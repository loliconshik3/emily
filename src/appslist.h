#ifndef APPSLIST_H
#define APPSLIST_H

#include <QListWidget>
#include <QMainWindow>
#include "mainwindow.h"

class AppsList : public QListWidget
{
    Q_OBJECT

public:
    std::map<std::string, std::string> apps;
    MainWindow *parent;

public:
    AppsList(MainWindow *parent = nullptr);
    void LoadAppsList();
    void redrawApps();

private slots:
    void updateStyle();
    void updateConnections();

protected:
    void keyPressEvent(QKeyEvent *e);
};

#endif // APPSLIST_H
