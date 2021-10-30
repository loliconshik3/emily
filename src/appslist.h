#ifndef APPSLIST_H
#define APPSLIST_H

#include <QListWidget>
#include <QMainWindow>
#include "mainwindow.h"

class MainWindow::AppsList : public QListWidget
{
    Q_OBJECT

public:
    std::map<std::string, std::string> apps;
    MainWindow *parent;

public:
    AppsList(MainWindow *parent = nullptr);
    ~AppsList();
    void LoadAppsList();
    void redrawApps();

private slots:
    void onItemClicked(QListWidgetItem* item);

protected:
    void keyPressEvent(QKeyEvent *e);
};

#endif // APPSLIST_H
