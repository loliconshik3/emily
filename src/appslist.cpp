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

AppsList::AppsList(MainWindow *parent)
    : QListWidget(parent)
{
    this->parent = parent;

    updateStyle();
    updateConnections();
    LoadAppsList();
}

void AppsList::LoadAppsList() {
    ifstream myfile;
    string line;

    string path = "/usr/share/applications";
        for (const auto & entry : fs::directory_iterator(path)){
            QFile file(entry.path().c_str());
            myfile.open(entry.path());

            if ( myfile.is_open() and file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                string execute;
                string filename;

                bool isAppDisplayed = true;
                bool isTerminalUtil = false;

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

                    findIndex = line.find("NoDisplay=true");
                    if (findIndex != -1) {
                        isAppDisplayed = false;
                    }
                }

                if (isAppDisplayed && filename != "" && apps[filename] == "" && execute != "") {
                    if (isTerminalUtil) {
                        QString repTermCom = parent->cfg.terminalCommand.c_str();
                        repTermCom.replace("$dir$", getHomeDir().c_str());
                        string termCom = repTermCom.toStdString();
                        execute = termCom + execute;
                    }

                    apps[filename] = execute;

                    QListWidgetItem *item = new QListWidgetItem(filename.c_str());
                    item->setToolTip(execute.c_str());
                    addItem(item);
                }
            }

            myfile.close();
        }

    sortItems();
    setCurrentItem(item(0));
}

void AppsList::redrawApps() {
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

void AppsList::keyPressEvent(QKeyEvent *e) {
    auto key = e->key();

    if (key!= Qt::Key_Up and key != Qt::Key_Down and key != Qt::Key_Left and key != Qt::Key_Right) {
        this->parent->textbox->setFocus();
        this->parent->textbox->insert(e->text());
    }
}

void AppsList::updateStyle() {
    int x       = parent->cfg.listPaddingX;
    int y       = parent->cfg.listPaddingY;
    int width   = parent->cfg.listWidth;
    int height  = parent->cfg.listHeight;

    // Set style of widget
    setGeometry(x, y, width, height);
    string style = "QListWidget { border: none; background: " + parent->colorScheme.backgroundColor + "; color: " + parent->colorScheme.foregroundColor + "; }";
    style += "QListWidget::item:selected { border: none; background-color: " + parent->colorScheme.selectedColor + "; }";

    setStyleSheet(style.c_str());

    // Set font of widget text
    QFont font = QFont("Source Code Pro");
    font.setPixelSize(parent->height * 0.7);
    setFont(font);

    // Remove scrollbars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSpacing(2);

    if (parent->cfg.horizontalList) {
        setFlow(QListWidget::LeftToRight);
    }
}

void AppsList::updateConnections() {
    connect(this, &AppsList::itemClicked, this, [this]{ this->parent->launch(); });
}
