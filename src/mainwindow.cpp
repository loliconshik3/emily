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
    updateStyle();
    updateConnections();
}

void MainWindow::swapList() {
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
            std::exit(1);
        }

        itemName = appsList->currentItem()->text().toUtf8().constData();

        std::cout << itemName << std::endl;
        executeString = appsList->apps[itemName];

    } else if (not scriptsList->isHidden()) {
        if ( scriptsList->count() == 0 ) {
            std::exit(1);
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

    isLaunching = true;
    hide();
    CreateProcess(execute.c_str(), params.c_str());
    std::exit(0);
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

void MainWindow::updateStyle() {
    //===Window settings===
    setWindowTitle("emily");

    QSize size = QSize(cfg.windowWidth, cfg.windowHeight);

    setMinimumSize(size);
    setMaximumSize(size);
    move(cfg.windowX, cfg.windowY);

    if (cfg.isPopup) {
        setWindowFlags(Qt::Popup);
    }

    setStyleSheet(("MainWindow { background: " + colorScheme.backgroundColor + "; }").c_str());
}

void MainWindow::updateConnections() {
    QShortcut *shortcut = new QShortcut(QKeySequence("Down"), this);
    connect(shortcut, &QShortcut::activated, this, &MainWindow::scrollDown);

    shortcut = new QShortcut(QKeySequence("Up"), this);
    connect(shortcut, &QShortcut::activated, this, &MainWindow::scrollUp);

    shortcut = new QShortcut(QKeySequence("Return"), this);
    connect(shortcut, &QShortcut::activated, this, &MainWindow::launch);

    shortcut = new QShortcut(QKeySequence("Enter"), this);
    connect(shortcut, &QShortcut::activated, this, &MainWindow::launch);

    shortcut = new QShortcut(QKeySequence("Tab"), this);
    connect(shortcut, &QShortcut::activated, this, &MainWindow::swapList);

    shortcut = new QShortcut(QKeySequence("Escape"), this);
    connect(shortcut, &QShortcut::activated, this, []{ std::exit(0); });
}


