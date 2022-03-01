#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

class Database
{
public:
    Database();
    QSqlDatabase db;
    void close();

private:
    bool createConnection();
    bool createTables();
    bool addValueToRestaurantTable(QString, QString, QString,QString,QString,QString,QString);
    bool initialRestaurant();
};

#endif // DATABASE_H
