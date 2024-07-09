#include "mainwindow.h"
#include "login.h"
#include <QApplication>
#include <QJsonDocument>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
    login w;
    w.show();
    return a.exec();
}
