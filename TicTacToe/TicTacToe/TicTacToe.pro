QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TicTacToe
TEMPLATE = app


SOURCES += main.cpp\
    tictactoe.cpp \
    mainMenu.cpp \
    mainWindow.cpp \
    mainBtnClick.cpp \
    about.cpp

HEADERS  += \
    tictactoe.h \
    mainWindow.h \
    about.h

FORMS    += mainwindow.ui \
    about.ui

RESOURCES += \
    res.qrc
