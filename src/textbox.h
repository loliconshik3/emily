#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "mainwindow.h"
#include "appslist.h"

#include <QLineEdit>
#include <string>
#include <fstream>
#include <iostream>

class Textbox : public QLineEdit
{
    Q_OBJECT
public:
    MainWindow *parent;

public:
    Textbox(MainWindow *parent=nullptr);

private slots:
    void updateStyle();
    void updateConnections();
    void filterList();

protected:
    void keyPressEvent(QKeyEvent *event) {
        if(event->key() == Qt::Key_Left or event->key() == Qt::Key_Up){
            parent->scrollUp();
        }
        else if(event->key() == Qt::Key_Right or event->key() == Qt::Key_Down){
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
