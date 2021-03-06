#include "config.h"
#include "utils.h"

#include <QSettings>
#include <QFile>

Config::Config()
{
    addConfigFile();
    loadConfigFile();
}

void Config::addConfigFile() {
    QString homedir = getHomeDir().c_str();
    QFile fl(homedir + "/.config/emily/config.ini");
    bool exists = fl.exists();

    if (!exists) {
        QSettings* settings = new QSettings(homedir + "/.config/emily/config.ini", QSettings::IniFormat);

        settings->setValue("UI/colorScheme",     colorScheme.c_str());
        settings->setValue("UI/userInterface",   userInterface.c_str());
        settings->setValue("USER/terminalCommand", terminalCommand.c_str());

        settings->setValue("DMENU/width", dmenuWidth);
        settings->setValue("DMENU/height", dmenuHeight);
        settings->setValue("DMENU/windowX", dmenuWindowX);
        settings->setValue("DMENU/windowY", dmenuWindowY);

        settings->sync();
    }
}

void Config::loadConfigFile() {
    QString homedir = getHomeDir().c_str();
    QSettings settings(QString(homedir + "/.config/emily/config.ini"), QSettings::IniFormat);

    colorScheme     = settings.value("UI/colorScheme", colorScheme.c_str()).toString().toStdString();
    userInterface   = settings.value("UI/userInterface", userInterface.c_str()).toString().toStdString();
    terminalCommand = settings.value("USER/terminalCommand", terminalCommand.c_str()).toString().toStdString();

    dmenuWidth      = settings.value("DMENU/width", dmenuWidth).toInt();
    dmenuHeight     = settings.value("DMENU/height", dmenuHeight).toInt();
    dmenuWindowX    = settings.value("DMENU/windowX", dmenuWindowX).toInt();
    dmenuWindowY    = settings.value("DMENU/windowY", dmenuWindowY).toInt();

    if (userInterface == ROFI_UI) {
        generateRofiUI();
    }
    else if (userInterface == DMENU_UI) {
        generateDmenuUI();
    }
}

void Config::generateRofiUI() {
    width   = maxWidth / 2;
    height  = maxHeight / 3;

    windowWidth     = width;
    windowHeight    = height;
    windowX         = (maxWidth - width) / 2;
    windowY         = (maxHeight - height) / 2;

    textBoxPaddingX = 5;
    textBoxPaddingY = 5;
    textBoxWidth    = width-textBoxPaddingX*2;
    textBoxHeight   = 25;
    listPaddingX    = 5;
    listPaddingY    = 30;
    listWidth       = width-listPaddingX*2;
    listHeight      = height-listPaddingY-textBoxPaddingY;
    horizontalList  = false;
    isPopup         = false;
}

void Config::generateDmenuUI() {
    width   = maxWidth / 4;
    height  = maxHeight * 0.025;

    windowWidth     = maxWidth;
    windowHeight    = height;
    windowX         = 0;
    windowY         = 0;

    if (dmenuWidth != windowWidth and dmenuWidth != 0) windowWidth = dmenuWidth;
    if (dmenuHeight != windowHeight and dmenuHeight != 0) windowHeight = dmenuHeight;
    if (dmenuWindowX != windowX) windowX = dmenuWindowX;
    if (dmenuWindowY != windowY) windowY = dmenuWindowY;

    textBoxPaddingX = 5;
    textBoxPaddingY = 0;
    textBoxWidth    = width;
    textBoxHeight   = windowHeight;
    listPaddingX    = width+5;
    listPaddingY    = 0;
    listWidth       = windowWidth - width;
    listHeight      = windowHeight;
    horizontalList  = true;
    isPopup         = true;
}
