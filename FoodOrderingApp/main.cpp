#include <QApplication>
#include "homepage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HomePage h;
    h.show();
    return a.exec();
}
