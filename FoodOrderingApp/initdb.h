#ifndef INITDB_H
#define INITDB_H

#include <QtSql>
#include <QList>
#include <QMessageBox>

QSqlDatabase db;
void closeDB();

//QVariant addBook(QSqlQuery &q, const QString &title, double price, const QVariant &authorId,
//             const QVariant &genreId, int rating)
//{
//    q.addBindValue(title);
//    q.addBindValue(price);
//    q.addBindValue(authorId);
//    q.addBindValue(genreId);
//    q.addBindValue(rating);
//    q.exec();
//    return q.lastInsertId();
//}

//QVariant addGenre(QSqlQuery &q, const QString &name)
//{
//    q.addBindValue(name);
//    q.exec();
//    return q.lastInsertId();
//}

//QVariant addAuthor(QSqlQuery &q, const QString &name, QDate birthdate)
//{
//    q.addBindValue(name);
//    q.addBindValue(birthdate);
//    q.exec();
//    return q.lastInsertId();
//}

//// newly added
//void addProperty(QSqlQuery &q, const QString &property, const QString &propertyJSON, const QVariant &bookId,
//             const QString propertyType)
//{
//    q.addBindValue(property);
//    q.addBindValue(propertyJSON);
//    q.addBindValue(bookId);
//    q.addBindValue(propertyType);
//    q.exec();
//}

//QVariant addPropertyType(QSqlQuery &q, const QString &name)
//{
//    q.addBindValue(name);
//    q.exec();
//    return q.lastInsertId();
//}

//const auto PROPERTIES_SQL = QLatin1String(R"(
//    create table properties(id integer primary key, property varchar, propertyJSON varchar, book integer, propertyType varchar)
//    )");

//const auto BOOKS_SQL = QLatin1String(R"(
//    create table books(id integer primary key, title varchar, author integer,
//                       genre integer, price double, rating integer)
//    )");

//const auto AUTHORS_SQL =  QLatin1String(R"(
//    create table authors(id integer primary key, name varchar, birthdate date)
//    )");

//const auto GENRES_SQL = QLatin1String(R"(
//    create table genres(id integer primary key, name varchar)
//    )");

//const auto INSERT_PROPERTY_SQL = QLatin1String(R"(
//    insert into properties(property, propertyJSON, book, propertyType)
//                      values(?, ?, ?, ?)
//    )");

//const auto INSERT_AUTHOR_SQL = QLatin1String(R"(
//    insert into authors(name, birthdate) values(?, ?)
//    )");

//const auto INSERT_BOOK_SQL = QLatin1String(R"(
//    insert into books(title, price, author, genre, rating)
//                      values(?, ?, ?, ?, ?)
//    )");
//const auto INSERT_GENRE_SQL = QLatin1String(R"(
//    insert into genres(name) values(?)
//    )");

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

QSqlError initDb()
{
    qDebug()<<"init";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Users/yangxueying/Desktop/OOP-project/QtDB.db");

    if (!db.open())
        return db.lastError();
    qDebug()<< "drive" << QSqlDatabase::drivers();
    qDebug()<< "end" << db.databaseName();

//    QStringList tables = db.tables();
//    if (tables.contains("books", Qt::CaseInsensitive)
//        && tables.contains("authors", Qt::CaseInsensitive))
//        return QSqlError();

//    QSqlQuery q;
//    if (!q.exec(BOOKS_SQL))
//        return q.lastError();
//    if (!q.exec(AUTHORS_SQL))
//        return q.lastError();
//    if (!q.exec(GENRES_SQL))
//        return q.lastError();
//    if (!q.exec(PROPERTIES_SQL))
//        return q.lastError();
//    if (!q.exec(PROPERTYTYPES_SQL))
//        return q.lastError();

//    if (!q.prepare(INSERT_AUTHOR_SQL))
//        return q.lastError();
//    QVariant asimovId = addAuthor(q, QLatin1String("Isaac Asimov"), QDate(1920, 2, 1));
//    QVariant greeneId = addAuthor(q, QLatin1String("Graham Greene"), QDate(1904, 10, 2));
//    QVariant pratchettId = addAuthor(q, QLatin1String("Terry Pratchett"), QDate(1948, 4, 28));

//    if (!q.prepare(INSERT_GENRE_SQL))
//        return q.lastError();
//    QVariant sfiction = addGenre(q, QLatin1String("Science Fiction"));
//    QVariant fiction = addGenre(q, QLatin1String("Fiction"));
//    QVariant fantasy = addGenre(q, QLatin1String("Fantasy"));

//    if (!q.prepare(INSERT_BOOK_SQL))
//        return q.lastError();
//    QVariant f1 = addBook(q, QLatin1String("Foundation"), 12.50, asimovId, sfiction, 3);
//    QVariant f2 = addBook(q, QLatin1String("Foundation and Empire"), 20, asimovId, sfiction, 4);
//    QVariant f3 = addBook(q, QLatin1String("Second Foundation"), 17, asimovId, sfiction, 3);
//    QVariant f4 = addBook(q, QLatin1String("Foundation's Edge"), 14.9, asimovId, sfiction, 3);
//    QVariant f5 = addBook(q, QLatin1String("Foundation and Earth"), 18, asimovId, sfiction, 4);
//    QVariant f6 = addBook(q, QLatin1String("Prelude to Foundation"), 22, asimovId, sfiction, 3);
//    QVariant f7 = addBook(q, QLatin1String("Forward the Foundation"), 15.9, asimovId, sfiction, 3);
//    QVariant g1 = addBook(q, QLatin1String("The Power and the Glory"), 80, greeneId, fiction, 4);
//    QVariant g2 = addBook(q, QLatin1String("The Third Man"), 30, greeneId, fiction, 5);
//    QVariant g3 = addBook(q, QLatin1String("Our Man in Havana"), 15, greeneId, fiction, 4);
//    QVariant p1 = addBook(q, QLatin1String("Guards! Guards!"), 77, pratchettId, fantasy, 3);
//    QVariant p2 = addBook(q, QLatin1String("Night Watch"), 32.1, pratchettId, fantasy, 3);
//    QVariant p3 = addBook(q, QLatin1String("Going Postal"), 5.49, pratchettId, fantasy, 3);


////    if (!q.prepare(INSERT_PROPERTYTYPE_SQL))
////        return q.lastError();
////    QVariant singleSelect = addPropertyType(q, QLatin1String("single select"));
////    QVariant multiSelect = addPropertyType(q, QLatin1String("multi-select"));
////    QVariant text = addPropertyType(q, QLatin1String("text box"));


//    if (!q.prepare(INSERT_PROPERTY_SQL))
//        return q.lastError();
//    addProperty(q, QLatin1String("Size"), QLatin1String("{\"Regular\": 0,\"Large\": 2.5}"), f1, QLatin1String("single select"));
//    addProperty(q, QLatin1String("Size"), QLatin1String("{\"Regular\": 0,\"Large\": 2}"), g1, QLatin1String("single select"));
//    addProperty(q, QLatin1String("Base"), QLatin1String("{\"White Rice\": 0,\"Brown Rice\": 1,\"Mixed Veggie\": 1}"), f1, QLatin1String("single select"));
//    addProperty(q, QLatin1String("Protein"), QLatin1String("{\"Chicken\": 2,\"Pork\": 2,\"Beef\": 3}"), f1, QLatin1String("single select"));
//    addProperty(q, QLatin1String("Addon"), QLatin1String("{\"Mushroom\": 1.5,\"Carrot\": 1,\"Cucumber\": 1}"), f1, QLatin1String("multi-select"));
//    addProperty(q, QLatin1String("Addon"), QLatin1String("{\"Mushroom\": 1.5,\"Carrot\": 1,\"Cucumber\": 1}"), g1, QLatin1String("multi-select"));

//    QSqlQuery q;
//    if (!q.prepare(INSERT_PROPERTY_SQL))
//        return q.lastError();
//    addProperty(q, QLatin1String("Size"), QLatin1String("{\"Regular\": 0,\"Large\": 2.5}"), QLatin1String("Thai"), QLatin1String("single select"));
//    addProperty(q, QLatin1String("Size"), QLatin1String("{\"Regular\": 0,\"Large\": 2}"), QLatin1String("Pizza"), QLatin1String("single select"));
//    addProperty(q, QLatin1String("Base"), QLatin1String("{\"White Rice\": 0,\"Brown Rice\": 1,\"Mixed Veggie\": 1}"), QLatin1String("Thai"), QLatin1String("single select"));
//    addProperty(q, QLatin1String("Protein"), QLatin1String("{\"Chicken\": 2,\"Pork\": 2,\"Beef\": 3}"), QLatin1String("Thai"), QLatin1String("single select"));
//    addProperty(q, QLatin1String("Addon"), QLatin1String("{\"Mushroom\": 1.5,\"Carrot\": 1,\"Cucumber\": 1}"), QLatin1String("Thai"), QLatin1String("multi-select"));
//    addProperty(q, QLatin1String("Addon"), QLatin1String("{\"Mushroom\": 1.5,\"Carrot\": 1,\"Cucumber\": 1}"), QLatin1String("Pizza"), QLatin1String("multi-select"));

    return QSqlError();
}

#endif
