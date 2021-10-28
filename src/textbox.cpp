#include "textbox.h"
#include "mainwindow.h"
#include "scriptslist.h"
#include "appslist.h"

#include <QShortcut>
#include <string>
#include <fstream>
#include <iostream>

MainWindow::Textbox::Textbox(MainWindow *parent)
    : QLineEdit(parent)
{
    this->parent = parent;
    setGeometry(5, 0, parent->maxWidth/8, 25);
    setStyleSheet("QLineEdit { font-size: 16px; qproperty-frame: false; background: #2f343f; color: lightGray; font-family: Source Code Pro; }");
    setPlaceholderText("Apps...");
    setCursor(Qt::ArrowCursor);

    connect(this, &Textbox::textChanged, this, &Textbox::filterList);
}

void MainWindow::Textbox::filterList() {
    if (not parent->appsList->isHidden()) {
        parent->appsList->redrawApps();
    } else if (not parent->scriptsList->isHidden()) {
        parent->scriptsList->redrawScripts();
    }
}
