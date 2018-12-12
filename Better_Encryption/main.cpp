//Copyright © 2018, [Austin Draper](https://github.com/Austin-Draper).
#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
