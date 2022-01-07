#include "utils.h"

/*#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <wait.h>

#include <fstream>
#include <iostream>
#include <filesystem>

#include <sys/types.h>
#include <pwd.h>

string getHomeDir() {
    string homedir;

    if ((homedir = getenv("HOME")).c_str() == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }

    return homedir;
}

pid_t CreateProcess(const char* command, const char* parametersIn)
{
    const int maxNumArgs = 1024;
    const char* args[maxNumArgs];
    char* parameters = NULL;

    memset(args, 0, (sizeof(char*) * maxNumArgs));
    args[0] = command;

    if(parametersIn != NULL)
    {
        parameters = strdup(parametersIn);
        int strLen = strlen(parameters);

        int numParameters = 1;
        bool expectNextParam = true;
        int i;
        for(i = 0; i < strLen; i++)
        {
            if(parameters[i] == ' ' || parameters[i] == '\t' ||
               parameters[i] == '\n')
            {
                expectNextParam = true;
                parameters[i] = '\0';
            }
            else if(expectNextParam)
            {
                args[numParameters] = &(parameters[i]);
                numParameters++;
                expectNextParam = false;
            }
        }
    }

    pid_t pid = fork();
    if(pid == 0)
    {
        if (execvp(command, (char**)args) < 0) {
            printf("Failed!");
        }
        _exit(1);
    }

    if(parameters != NULL)
        free(parameters);

    waitpid(pid, NULL, 0);

    return pid;
}

void split(string &str, char delim, vector<string> &out)
{
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

/*QPixmap extractMime(const QString &sourceFile)
{
    QMimeDatabase mime_database;
    const QString nativeName = QDir::toNativeSeparators(sourceFile);
    QIcon icon;
    QList<QMimeType> mime_types = mime_database.mimeTypesForFileName(nativeName);
    icon = QIcon::fromTheme(mime_types[0].iconName());
    if (icon.isNull())  qDebug() << "null";
    qDebug() << mime_types[0].iconName();
    return icon.pixmap(16);
}*/

/*int exec(const char* cmd) {
    pid_t child_pid;
    child_pid = fork (); // Create a new child process;
    if (child_pid < 0) {
       printf("fork failed");
       return 1;
    } else if (child_pid == 0) {
       printf ("child process successfully created!\n");
       printf ("child_PID = %d,parent_PID = %d\n",
       getpid(), getppid( ) );
    } else {
        char* test;
        exec(cmd, &test);
        printf("work!");
    }
    return 0;

    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}*/
