#include "restaurant.h"
#include "global.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    global_cart = new Cart();
    global_cart = Cart::GetInstance(0);

    Restaurant w;
    w.show();
    return a.exec();
}
