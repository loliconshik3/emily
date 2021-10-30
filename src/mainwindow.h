#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QRect rect = QDesktopWidget().availableGeometry();
public:
    int maxWidth = rect.width();
    int maxHeight = rect.height();
    int width = maxWidth / 4;
    int height = maxHeight * 0.03;

    class ScriptsList;
    class AppsList;
    class Textbox;

    AppsList *appsList;
    Textbox *textbox;
    ScriptsList *scriptsList;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void launch();
    void scrollUp();
    void scrollDown();
    void swapList();
    void Exit();

protected:
    void closeEvent(QCloseEvent *event) {
        std::exit(0);
    }
};
#endif // MAINWINDOW_H
