//#include "restaurant.h"
#include "cartdata.h"
#include <QApplication>
#include "homepage.h"
#include "Application.h"
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    HomePage h;
//    h.show();
//    return a.exec();
//}

int main(int argc, char *argv[])
{
    Application a(argc, argv);
//    QMainWindow m;
//    QDialog d;
//    QWidget w;
    HomePage h;
    h.show();
//    m.show();
//    d.show();
//    w.show();
    return a.exec();
}
