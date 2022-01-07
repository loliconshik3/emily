#ifndef UTILS_H
#define UTILS_H

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>

#include <QPixmap>
#include <QString>
#include <QMimeDatabase>
#include <QDir>
#include <QIcon>
#include <QDebug>
#include <QFileIconProvider>

using namespace std;

pid_t CreateProcess(const char* command, const char* parametersIn);
void split(string &str, char delim, vector<string> &out);
string getHomeDir();

#endif // UTILS_H
