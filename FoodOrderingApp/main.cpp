#include <QApplication>
#include "homepage.h"
#include "Application.h"

int main(int argc, char *argv[])
{
    Application a(argc, argv);
    HomePage h;
    h.show();
    return a.exec();
}
