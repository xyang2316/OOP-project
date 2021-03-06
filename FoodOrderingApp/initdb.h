#ifndef INITDB_H
#define INITDB_H

#include <QtSql>
#include <QList>
#include <QMessageBox>
#include "global.h"

QSqlDatabase db;
QSqlError initDb()
{
    qDebug()<<"init";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(Global::homePath  + "/QtDB.db");

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
