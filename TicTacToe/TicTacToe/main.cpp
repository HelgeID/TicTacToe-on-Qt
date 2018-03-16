#include "mainWindow.h"
#include <QApplication>

TicTacToe object;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow *window = new MainWindow(object);
    window->show();
    QObject::connect(window, SIGNAL(Exit()), &app, SLOT(quit()));
    return app.exec();
}
