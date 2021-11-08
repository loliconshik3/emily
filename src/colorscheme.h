#ifndef COLORSCHEME_H
#define COLORSCHEME_H

#include <string>

using namespace std;

class ColorScheme
{    
public:
    const string DIABLO_SCHEME = "Diablo";
    const string NORD_SCHEME   = "Nord";

    string backgroundColor = "";
    string foregroundColor = "";
    string selectedColor   = "";

    ColorScheme(string Name);

private:
    void generateDiablo();
    void generateNord();
};

#endif // COLORSCHEME_H
