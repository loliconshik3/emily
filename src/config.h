#ifndef CONFIG_H
#define CONFIG_H

#include "colorscheme.h"

#include <string>

#include <QDesktopWidget>
#include <QRect>

using namespace std;

class Config
{
private:
    QRect rect = QDesktopWidget().availableGeometry();
    ColorScheme csm = ColorScheme("");

    void generateRofiUI();
    void generateDmenuUI();

public:
    const string ROFI_UI    = "Rofi";
    const string DMENU_UI   = "Dmenu";

    string colorScheme      = csm.DIABLO_SCHEME;
    string userInterface    = ROFI_UI;

    int maxWidth    = rect.width();
    int maxHeight   = rect.height();
    int width       = 0;
    int height      = 0;


    int windowX         = 0;
    int windowY         = 0;
    int windowWidth     = 0;
    int windowHeight    = 0;
    int textBoxPaddingX = 0;
    int textBoxPaddingY = 0;
    int textBoxWidth    = 0;
    int textBoxHeight   = 0;
    int listPaddingX    = 0;
    int listPaddingY    = 0;
    int listWidth       = 0;
    int listHeight      = 0;
    bool horizontalList = false;

    Config();
};

#endif // CONFIG_H
