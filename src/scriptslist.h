#ifndef SCRIPTSLIST_H
#define SCRIPTSLIST_H

#include <QListWidget>
#include <QMainWindow>
#include "mainwindow.h"

class ScriptsList : public QListWidget
{
    Q_OBJECT

public:
    std::map<std::string, std::string> scripts;
    MainWindow *parent;

public:
    ScriptsList(MainWindow *parent = nullptr);
    void LoadScriptsList();
    void redrawScripts();

private slots:
    void updateStyle();
    void updateConnections();

protected:
    void keyPressEvent(QKeyEvent *e);
};

#endif // SCRIPTSLIST_H
