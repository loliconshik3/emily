#include "mainwindow.h"
#include "scriptslist.h"
#include "textbox.h"
#include "appslist.h"
#include "utils.h"

#include <QShortcut>
#include <QAction>
#include <QtWidgets>
#include <QtCore>

#include <string>
#include <fstream>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //===Window settings===
    setWindowTitle("emily");
    setMinimumSize(QSize(maxWidth, height));
    setMaximumSize(QSize(maxWidth, height));

    //move(0, maxHeight-25);

/*    int width = maxWidth / 3;
    int height = maxHeight / 4;

    setGeometry(0, 0, width, height);

    move((maxWidth-width)/2, (maxHeight-height)/2);
*/

    setStyleSheet(("QMainWindow { background: " + colorScheme.backgroundColor + "; }").c_str());
    setWindowFlags(Qt::CustomizeWindowHint | Qt::Popup);

    QShortcut *shortcut = new QShortcut(QKeySequence("Escape"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(Exit()));

    shortcut = new QShortcut(QKeySequence("Down"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(scrollDown()));

    shortcut = new QShortcut(QKeySequence("Up"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(scrollUp()));

    shortcut = new QShortcut(QKeySequence("Return"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(launch()));

    shortcut = new QShortcut(QKeySequence("Tab"), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(swapList()));
}

void MainWindow::swapList() {
    //textbox->clear();

    if (not appsList->isHidden()) {
        appsList->hide();
        scriptsList->show();
        scriptsList->redrawScripts();
        textbox->setPlaceholderText("Scripts...");

    } else if (not scriptsList->isHidden()) {
        scriptsList->hide();
        appsList->show();
        appsList->redrawApps();
        textbox->setPlaceholderText("Apps...");
    }
}

void MainWindow::launch() {
    std::string itemName;
    std::string executeString;

    if (not appsList->isHidden()) {
        if ( appsList->count() == 0 ) {
            Exit();
        }

        itemName = appsList->currentItem()->text().toUtf8().constData();

        std::cout << itemName << std::endl;
        executeString = appsList->apps[itemName];

    } else if (not scriptsList->isHidden()) {
        if ( scriptsList->count() == 0 ) {
            Exit();
        }

        itemName = scriptsList->currentItem()->text().toUtf8().constData();

        std::cout << itemName << std::endl;
        executeString = scriptsList->scripts[itemName];
    }

    std::string execute = executeString;
    std::string params = "";

    if (executeString.find(" ") != std::string::npos){
        char sep = ' ';
        vector<string> out;
        split(executeString, sep, out);

        execute = out[0].c_str();
        out.erase(out.begin());

        for (const auto &arg : out) {
            params.append(" " + arg);
        }
    }

    std::cout << execute << " *" << std::endl;
    std::cout << params << " *" << std::endl;

    hide();
    CreateProcess(execute.c_str(), params.c_str());
    Exit();
}

void MainWindow::scrollUp() {
    if (not appsList->isHidden()) {
        int itemIndex = appsList->currentIndex().row();
        int maxIndex = 0;

        if (itemIndex > maxIndex) {
            appsList->setCurrentItem(appsList->item(itemIndex-1));
        }
        /*else {
            appsList->setCurrentItem(appsList->item(appsList->count()-1));
        }*/
    } else if (not scriptsList->isHidden()) {
        int itemIndex = scriptsList->currentIndex().row();
        int maxIndex = 0;

        if (itemIndex > maxIndex) {
            scriptsList->setCurrentItem(scriptsList->item(itemIndex-1));
        }
    }
}

void MainWindow::scrollDown() {
    if (not appsList->isHidden()) {
        int itemIndex = appsList->currentIndex().row();
        int maxIndex = appsList->count()-1;

        if (itemIndex < maxIndex) {
           appsList->setCurrentItem(appsList->item(itemIndex+1));
        }
        /*else {
            appsList->setCurrentItem(appsList->item(0));
        }*/
    } else if (not scriptsList->isHidden()) {
        int itemIndex = scriptsList->currentIndex().row();
        int maxIndex = scriptsList->count()-1;

        if (itemIndex < maxIndex) {
           scriptsList->setCurrentItem(scriptsList->item(itemIndex+1));
        }
    }
}

void MainWindow::Exit() {
    std::exit(0);
}

MainWindow::~MainWindow()
{
}
