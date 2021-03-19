#include "HSearch.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HSearch w;
    w.show();
    return a.exec();
}
