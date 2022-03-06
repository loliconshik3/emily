#include "mainwindow.h"
#include "appslist.h"
#include "scriptslist.h"
#include "textbox.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    system("mkdir ~/.conifg/emily");
    system("mkdir ~/emily");

    app.setCursorFlashTime(0);
    MainWindow window;

    AppsList appsList(&window);
    Textbox textbox(&window);
    ScriptsList scriptsList(&window);

    window.appsList = &appsList;
    window.textbox = &textbox;
    window.scriptsList = &scriptsList;

    window.show();
    window.textbox->show();
    window.appsList->show();
    window.scriptsList->hide();
    window.textbox->setFocus();

    return app.exec();
}
