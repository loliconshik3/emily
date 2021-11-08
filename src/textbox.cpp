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

    int x       = parent->cfg.textBoxPaddingX;
    int y       = parent->cfg.textBoxPaddingY;
    int width   = parent->cfg.textBoxWidth;
    int height  = parent->cfg.textBoxHeight;

    setGeometry(x, y, width, height);
    //setGeometry(5, 0, parent->width, parent->height);

    string style = "QLineEdit { qproperty-frame: false; background: " + parent->colorScheme.backgroundColor + "; color: " + parent->colorScheme.foregroundColor + "; }";
    setStyleSheet(style.c_str());

    //setStyleSheet("QLineEdit { qproperty-frame: false; background: #2f343f; color: lightGray; }");
    setPlaceholderText("Apps...");
    setCursor(Qt::ArrowCursor);

    QFont font = QFont("Source Code Pro");
    font.setPixelSize(parent->height * 0.7);
    setFont(font);

    connect(this, &Textbox::textChanged, this, &Textbox::filterList);
}

void MainWindow::Textbox::filterList() {
    if (not parent->appsList->isHidden()) {
        parent->appsList->redrawApps();
    } else if (not parent->scriptsList->isHidden()) {
        parent->scriptsList->redrawScripts();
    }
}
