#include "restaurant.h"

Restaurant::Restaurant()
{


}

Restaurant::Restaurant(int rid, QString rname, QString raddress, QString rcity, QString rstate, QString rzip, QString rphone){
    id = rid;
    name = rname;
    address = raddress;
    city = rcity;
    state = rstate;
    zip = rzip;
    phone = rphone;
}

int Restaurant::getId(){
    return id;
}

QString Restaurant::getName(){
    return name;
}
