#include "foodiepalace.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FoodiePalace w;
    w.show();
    return a.exec();
}
