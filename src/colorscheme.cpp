#include "colorscheme.h"

ColorScheme::ColorScheme(string Name)
{
    if (Name == DIABLO_SCHEME) {
        generateDiablo();
    }
    else if (Name == NORD_SCHEME) {
        generateNord();
    }
}

void ColorScheme::generateDiablo() {
    this->backgroundColor = "#303030";
    this->foregroundColor = "#f3f4f5";
    this->selectedColor   = "#ff0046";
}

void ColorScheme::generateNord() {
    this->backgroundColor = "#2f343f";
    this->foregroundColor = "#f3f4f5";
    this->selectedColor   = "#4c566a";
}
