#include "appslist.h"
#include "mainwindow.h"
#include "textbox.h"
#include "utils.h"

#include <QAction>
#include <QtWidgets>
#include <QShortcut>
#include <QtCore>
#include <QUrl>

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

MainWindow::AppsList::AppsList(MainWindow *parent)
    : QListWidget(parent)
{
    this->parent = parent;

    int x       = parent->cfg.listPaddingX;
    int y       = parent->cfg.listPaddingY;
    int width   = parent->cfg.listWidth;
    int height  = parent->cfg.listHeight;

    setGeometry(x, y, width, height);
    //setGeometry(parent->width+5, 0, parent->maxWidth - parent->width, parent->height);
    string style = "QListWidget { border: none; background: " + parent->colorScheme.backgroundColor + "; color: " + parent->colorScheme.foregroundColor + "; }";
    style += "QListWidget::item:selected { border: none; background-color: " + parent->colorScheme.selectedColor + "; }";

    /*setStyleSheet("QListWidget { border: none; background: #2f343f; color: lightGray; }"
                  "QListWidget::item:selected { border: none; background-color: #4c566a; }");*/
    setStyleSheet(style.c_str());

    QFont font = QFont("Source Code Pro");
    font.setPixelSize(parent->height * 0.7);
    setFont(font);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSpacing(2);

    if (parent->cfg.horizontalList) {
        setFlow(QListWidget::LeftToRight);
    }

    //setIconSize(QSize(32,32));

    connect(this, &AppsList::itemClicked, this, &AppsList::onItemClicked);

    LoadAppsList();

}

void MainWindow::AppsList::LoadAppsList() {
    ifstream myfile;
    string line;

    string path = "/usr/share/applications";
        for (const auto & entry : fs::directory_iterator(path)){
            QFile file(entry.path().c_str());
            myfile.open(entry.path());

            if ( myfile.is_open() and file.open(QIODevice::ReadOnly | QIODevice::Text)) { // always check whether the file is open
                string execute;
                string filename;
                bool isTerminalUtil = false;

                /*QString filestr = file.readAll();
                QRegExp rx;
                rx = QRegExp("Name=(.*)\\s$");
                int index = rx.indexIn(filestr);
                int lng = rx.matchedLength();
                QStringRef subString(&filestr, index, lng);

                std::cout << index << " | " << lng << " | " << filestr.length() << " | " << rx.pattern().toStdString() << std::endl;
                */

                while (getline(myfile, line)) {
                    int findIndex = line.find("Exec=");
                    if (findIndex != -1 && execute == "") {
                        execute = line.substr(findIndex+5);

                        findIndex = execute.find("%");
                        if (findIndex != -1) {
                            execute = execute.substr(0, findIndex);
                        }

                    } else {
                        findIndex = line.find("Name=");
                        if (findIndex == 0 && filename == "") {
                            filename = line.substr(findIndex+5);
                        }
                    }

                    findIndex = line.find("Terminal=true");
                    if (findIndex == 0) {
                        isTerminalUtil = true;
                    }
                }

                if (filename != "" && apps[filename] == "" && execute != "") {
                    if (isTerminalUtil) {
                        QString repTermCom = parent->cfg.terminalCommand.c_str();
                        repTermCom.replace("$dir$", getHomeDir().c_str());
                        string termCom = repTermCom.toStdString();
                        execute = termCom + execute;
                    }

                    apps[filename] = execute;

                    addItem(filename.c_str());
                }
            }

            myfile.close();
        }

    sortItems();
    setCurrentItem(item(0));
}

void MainWindow::AppsList::redrawApps() {
    clear();

    for (const auto & file : apps) {
        std::string fileName = QString(file.first.c_str()).toLower().toUtf8().constData();
        std::string searchQuery = parent->textbox->text().toLower().toUtf8().constData();

        if ( fileName.find(searchQuery) != std::string::npos ) {
            addItem(QString(file.first.c_str()));
        }
    }

    sortItems();
    setCurrentItem(item(0));
}

void MainWindow::AppsList::keyPressEvent(QKeyEvent *e) {
    auto key = e->key();

    if (key!= Qt::Key_Up and key != Qt::Key_Down and key != Qt::Key_Left and key != Qt::Key_Right) {
        this->parent->textbox->setFocus();
        this->parent->textbox->insert(e->text());
    }
}

void MainWindow::AppsList::onItemClicked(QListWidgetItem* item) {
    parent->launch();
}

MainWindow::AppsList::~AppsList()
{
}
