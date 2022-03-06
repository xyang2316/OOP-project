//#include "restaurant.h"
#include "cartdata.h"
#include <QApplication>
#include "homepage.h"

int main(int argc, char *argv[])
{
//    createDBConnection();
    QApplication a(argc, argv);
//    Restaurant w;
    HomePage h;
    h.show();
    return a.exec();
}
