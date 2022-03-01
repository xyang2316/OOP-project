#ifndef RESTAURANT_H
#define RESTAURANT_H
#include<QString>

class Restaurant
{
private:
    int id;
    QString name;
    QString address;
    QString city;
    QString state;
    QString zip;
    QString phone;

public:
    Restaurant();
    Restaurant(int rid, QString rname, QString raddress, QString rcity, QString rstate, QString rzip, QString rphone);
    int getId();
    QString getName();
};

#endif // RESTAURANT_H
