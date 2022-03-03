#include "restaurant.h"
#include "global.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    global_cart = new Cart();
    Restaurant w;
    w.show();
    return a.exec();
}
