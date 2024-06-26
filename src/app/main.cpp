#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug()<<QCoreApplication::applicationDirPath();
    qDebug()<<QDir::currentPath();
    MainWindow w;
    w.show();
    return a.exec();
}
