#include "database.h"
#include "restaurant.h"
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

extern QVector<Restaurant>restaurantList;
Database::Database()
{
    createConnection();
    initialRestaurant();
};

bool Database::createConnection(){
    qDebug()<<"start";
    db = QSqlDatabase::addDatabase("QSQLITE", "connection");
    db.setDatabaseName("/Users/yangxueying/Desktop/OOP-project/QtDB.db");

    if(!db.open()){
        QMessageBox msg;
        msg.setText(QStringLiteral("Failed to open DB!"));
        msg.setWindowTitle(QStringLiteral("Error！"));
        msg.exec();
        qDebug()<<"!!";
        return false;
    }
    qDebug()<< "end" << db.databaseName();
    return true;
}

void Database::close(){
    db.close();
}

//collect info from db to a vector to render to front end
bool Database::initialRestaurant(){
    QSqlQuery query(db);
    query.exec("select * from Restaurant");
    while(query.next())
    {
        int id=query.value(0).toInt();
        QString name=query.value(1).toString();
        QString address=query.value(2).toString();
        QString city=query.value(3).toString();
        QString state=query.value(4).toString();
        QString zip=query.value(5).toString();
        QString phone=query.value(6).toString();
        Restaurant d(id, name, address, city, state, zip, phone);
        restaurantList.append(d);
    }
    return true;
}






//*******************************************************************************//

//below this: for fureture usage
bool Database::createTables()
{
    QSqlQuery query(db);
    //build restaurant table
    query.prepare("create table IF NOT EXISTS Restaurant"
                "(Id INTEGER PRIMARY KEY, "
                  "Name VARCHAR,"
                  "Address VARCHAR,"
                  "City VARCHAR,"
                  "State VARCHAR,"
                  "Zip VARCHAR,"
                  "Phone VARCHAR)");
    if(!query.exec())
    {       QMessageBox msg;
            msg.setText("Fatal error!Failed to create table Restaurant!");
            msg.setWindowTitle(QStringLiteral("Error！"));
            msg.exec();
            return false;}

    //build dish table
    query.prepare("create table IF NOT EXISTS Dish"
                "(DishId INTEGER PRIMARY KEY, "
                  "RestaurantName VARCHAR,"
                  "Price FLOAT,"
                  "Description VARCHAR)");
    if (!query.exec())
    {       QMessageBox msg;
            msg.setText("Fatal error!Failed to create table Dish!");
            msg.setWindowTitle(QStringLiteral("Error！"));
            msg.exec();
            return false;}

    //build e-wallet table
    query.prepare("create table IF NOT EXISTS Wallet"
                "(WalletId INTEGER PRIMARY KEY, "
                  "balance FLOAT)");
    if (!query.exec())
    {       QMessageBox msg;
            msg.setText("Fatal error!Failed to create table Wallet!");
            msg.setWindowTitle(QStringLiteral("Error！"));
            msg.exec();
            return false;}
    return true;
}


    //still in progress: populate data into database not
    //TODO: populate from file(.cvs, txt etc) instead of manually add them to db
    //add value function not working properly
//    addValueToRestaurantTable(db, "1", "Jasmine Thai", "1211 Franklin Mall", "Santa Clara", "CA", "95050", "4082463943");
//    addValueToRestaurantTable(db, "2", "Seniore's Pizza", "940 Monroe St", "Santa Clara", "CA", "95050", "4082612500");
bool Database::addValueToRestaurantTable(QString id, QString name, QString address, QString city, QString state, QString zip, QString phone){
    QSqlQuery query(db);
    query.prepare("INSERT INTO Restaurant"
                "(Id, Name, Address, City, State, Zip, Phone)"
                  "VALUES (?, ?, ? ,?, ?, ?, ?);");
    query.addBindValue(id);
    query.addBindValue(name);
    query.addBindValue(address);
    query.addBindValue(city);
    query.addBindValue(state);
    query.addBindValue(zip);
    query.addBindValue(phone);

    if (!query.exec())
    {       QMessageBox msg;
            msg.setText("Fatal error! Failed to insert value into table Restaurant!");
            msg.setWindowTitle(QStringLiteral("Error"));
            msg.exec();
            return false;}
    return true;
}




