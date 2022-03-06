#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "colorscheme.h"
#include "config.h"

#include <QMainWindow>
#include <QtWidgets>

#include <string>
#include <fstream>
#include <iostream>

class ScriptsList;
class AppsList;
class Textbox;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QRect rect = QDesktopWidget().availableGeometry();
public:
    bool isLaunching = false;
    Config cfg = Config();
    ColorScheme colorScheme = ColorScheme(cfg.colorScheme);

    int maxWidth = rect.width();
    int maxHeight = rect.height();
    int width = maxWidth / 4;
    int height = maxHeight * 0.025;

    AppsList *appsList;
    Textbox *textbox;
    ScriptsList *scriptsList;

public:
    MainWindow(QWidget *parent = nullptr);
    void launch();
    void scrollUp();
    void scrollDown();
    void swapList();

private slots:
    void updateStyle();
    void updateConnections();

protected:
    bool event(QEvent * e)
    {
        if (e->type() == QEvent::WindowDeactivate && !isLaunching) {
            std::exit(0);
        }
        return QMainWindow::event(e) ;
    }


    void closeEvent(QCloseEvent *event) {
        std::exit(0);
    }
};
#endif // MAINWINDOW_H
