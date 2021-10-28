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

namespace fs = std::filesystem;

MainWindow::AppsList::AppsList(MainWindow *parent)
    : QListWidget(parent)
{
    this->parent = parent;
    setGeometry(parent->maxWidth/8+5, 0, parent->maxWidth - parent->maxWidth/8, 25);
    setStyleSheet("QListWidget { border: none; font-size: 16px; background: #2f343f; color: lightGray; font-family: Source Code Pro; }"
                  "QListWidget::item:selected { border: none; background-color: #4c566a; }");

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFlow(QListWidget::LeftToRight);
    setSpacing(2);
    //setIconSize(QSize(32,32));

    connect(this, &AppsList::itemClicked, this, &AppsList::onItemClicked);

    LoadAppsList();

}

void MainWindow::AppsList::LoadAppsList() {
    std::ifstream myfile;
    std::string line;

    std::string path = "/usr/share/applications";
        for (const auto & entry : fs::directory_iterator(path)){
            myfile.open(entry.path());

            if ( myfile.is_open() ) { // always check whether the file is open
                std::string execute;
                std::string filename;
                std::string iconPath;

                while (getline(myfile, line)) {
                    int findIndex = line.find("Exec=");
                    if (findIndex == 0) {
                        execute = line.substr(findIndex+5);

                        findIndex = execute.find("%");
                        if (findIndex != -1) {
                            execute = execute.substr(0, findIndex);
                        }

                        /*findIndex = execute.find(" ");
                        if (findIndex != -1) {
                            execute = execute.substr(0, findIndex);
                        }*/

                    } else {
                        findIndex = line.find("Name=");
                        if (findIndex == 0) {
                            filename = line.substr(findIndex+5);
                        }
                    }

                    /*findIndex = line.find("NoDisplay=true");
                    if (findIndex == 0) {
                        std::cout << "anus" << std::endl;
                        break;
                    }*/

                    if (filename != "" and apps[filename] == "" and execute != "") {
                        apps[filename] = execute;

                        addItem(filename.c_str());
                        break;
                    }
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
