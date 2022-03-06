#include "restaurant.h"
#include "cartdata.h"
#include <QApplication>

int main(int argc, char *argv[])
{
//    createDBConnection();
    QApplication a(argc, argv);
    Restaurant w;
    w.show();
    return a.exec();
}
