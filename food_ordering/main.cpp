#include "mainwindow.h"
#include "database.h"
#include "restaurant.h"

#include <QApplication>
#include <QtSql>
#include <QDebug>

QVector<Restaurant>restaurantList;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Database myDB;
//    myDB.close();

    return a.exec();
}
