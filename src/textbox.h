#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <QLineEdit>
#include "mainwindow.h"
#include <string>
#include <fstream>
#include <iostream>

class MainWindow::Textbox : public QLineEdit
{
    Q_OBJECT
public:
    MainWindow *parent;

public:
    Textbox(MainWindow *parent=nullptr);

private slots:
    void filterList();

protected:
    void keyPressEvent(QKeyEvent *event) {
        if(event->key() == Qt::Key_Left){
            parent->scrollUp();
        }
        else if(event->key() == Qt::Key_Right){
            parent->scrollDown();
        }
        else{
            // default handler for event
            QLineEdit::keyPressEvent(event);
        }
    }

    void contextMenuEvent(QContextMenuEvent *event) {
        return;
    }
};

#endif // TEXTBOX_H
