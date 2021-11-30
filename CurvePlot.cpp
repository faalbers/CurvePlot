#include <QApplication>
#include "MainWindow.hpp"

int main(int argv, char **args)
{
    QApplication app(argv, args);
    MainWindow mainWindow;
   
    mainWindow.show();
    return app.exec();
}
