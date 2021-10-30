#include "scriptslist.h"
#include "mainwindow.h"
#include "textbox.h"

#include <QAction>
#include <QtWidgets>
#include <QShortcut>
#include <QtCore>

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

namespace fs = std::filesystem;

MainWindow::ScriptsList::ScriptsList(MainWindow *parent)
    : QListWidget(parent)
{
    this->parent = parent;
    setGeometry(parent->width+5, 0, parent->maxWidth - parent->width, parent->height);
    setStyleSheet("QListWidget { border: none; background: #2f343f; color: lightGray; }"
                  "QListWidget::item:selected { border: none; background-color: #4c566a;}");

    QFont font = QFont("Source Code Pro");
    font.setPixelSize(parent->height * 0.7);
    setFont(font);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFlow(QListWidget::LeftToRight);
    setSpacing(2);
    //setIconSize(QSize(32,32));

    connect(this, &ScriptsList::itemClicked, this, &ScriptsList::onItemClicked);

    LoadScriptsList();

}

void MainWindow::ScriptsList::LoadScriptsList() {
    std::ifstream myfile;
    std::string line;

    std::string homedir;

    if ((homedir = getenv("HOME")).c_str() == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }

    std::string path = homedir + "/emily";
        for (const auto & entry : fs::directory_iterator(path)){
            myfile.open(entry.path());

            if ( myfile.is_open() ) { // always check whether the file is open
                std::string execute;
                std::string filename;

                filename = entry.path().filename();
                int findIndex = filename.find(".sh");
                if (findIndex > -1) {
                    filename = filename.substr(0, findIndex);
                }

                execute = entry.path();

                scripts[filename] = "sh " + execute;
                addItem(filename.c_str());
            }

            myfile.close();
        }

    sortItems();
    setCurrentItem(item(0));
}

void MainWindow::ScriptsList::redrawScripts() {
    clear();

    for (const auto & file : scripts) {
        std::string fileName = QString(file.first.c_str()).toLower().toUtf8().constData();
        std::string searchQuery = parent->textbox->text().toLower().toUtf8().constData();

        if ( fileName.find(searchQuery) != std::string::npos ) {
            addItem(QString(file.first.c_str()));
        }
    }

    sortItems();
    setCurrentItem(item(0));
}

void MainWindow::ScriptsList::keyPressEvent(QKeyEvent *e) {
    auto key = e->key();

    if (key!= Qt::Key_Up and key != Qt::Key_Down and key != Qt::Key_Left and key != Qt::Key_Right) {
        this->parent->textbox->setFocus();
        this->parent->textbox->insert(e->text());
    }
}

void MainWindow::ScriptsList::onItemClicked(QListWidgetItem* item) {
    parent->launch();
}

MainWindow::ScriptsList::~ScriptsList()
{
}
