#ifndef INITDB_H
#define INITDB_H

#include <QtSql>
#include <QList>
#include <QMessageBox>

QSqlDatabase db;
QSqlError initDb()
{
    qDebug()<<"init";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    //please change to your local path to the DB
    db.setDatabaseName("/Users/yangxueying/Desktop/OOP-project/QtDB.db");

    if (!db.open())
        return db.lastError();
    qDebug()<< "drive" << QSqlDatabase::drivers();
    qDebug()<< "end" << db.databaseName();
    return QSqlError();
}

void closeDB()
{
    db.close();
    db.removeDatabase(QSqlDatabase::defaultConnection);
}

bool isDBOpen()
{
    if(db.open()) return true;
    return false;
}
#endif
