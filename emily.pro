QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 g++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/appslist.cpp \
    src/colorscheme.cpp \
    src/config.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/scriptslist.cpp \
    src/textbox.cpp \
    src/utils.cpp

HEADERS += \
    src/appslist.h \
    src/colorscheme.h \
    src/config.h \
    src/mainwindow.h \
    src/scriptslist.h \
    src/textbox.h \
    src/utils.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

