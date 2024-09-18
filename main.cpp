#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationName("Egor");
    QApplication::setApplicationName("Yeat");

    Widget w;
    w.show();

    return a.exec();
}
