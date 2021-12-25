#include "config.h"

Config::Config()
{
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
}

void Config::generateDmenuUI() {
    width   = maxWidth / 4;
    height  = maxHeight * 0.025;

    windowWidth     = maxWidth;
    windowHeight    = height;
    windowX         = 0;
    windowY         = 0;

    textBoxPaddingX = 5;
    textBoxPaddingY = 0;
    textBoxWidth    = width;
    textBoxHeight   = height;
    listPaddingX    = width+5;
    listPaddingY    = 0;
    listWidth       = maxWidth - width;
    listHeight      = height;
    horizontalList  = true;
}
