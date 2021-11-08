#ifndef CONFIG_H
#define CONFIG_H

#include "colorscheme.h"

#include <string>

using namespace std;

class Config
{
private:
    ColorScheme csm = ColorScheme("");

public:

    string colorScheme = csm.DIABLO_SCHEME;

    Config();
};

#endif // CONFIG_H
