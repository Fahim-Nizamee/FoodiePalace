#include "mainwindow.h"

#include <QApplication>
#include<QMap>
#include<string>
#include<iostream>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QMap<string, int>q;
    w.show();
    return a.exec();
}
