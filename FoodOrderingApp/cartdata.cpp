#include "cartdata.h"
#include <QDebug>

CartData::CartData()
{
    sumInCart = 0.0;
}

CartData* CartData::cartData_= nullptr;;

CartData *CartData::GetInstance() {
    if(cartData_==nullptr){
        cartData_ = new CartData();
    }
    return cartData_;
}

QList<QPair<int, double>> CartData::getPriceList() {
    return priceList;
}

QList<QList<QPair<QString, double>>> CartData::getCart() {
    return inCart;
}
double CartData::getSumInCart() {
    return sumInCart;
}

QString CartData::getInCartStr() {
    inCart = getCart();
    QString inCartStr;
    int i = 1;
    qDebug()<< "inside cartdata1"<< inCart;
    for (auto& dishList: inCart)
    {
        qDebug()<< "inside cartdata"<< dishList;
        inCartStr += "Dish " + QString::number(i) + ": ";
        for(auto& eachPair:dishList)
        {
            inCartStr += eachPair.first + " ";
            inCartStr += "$" + QString::number(eachPair.second) + " ";
        }
        inCartStr += "; ";
        i ++;
    }
    qDebug()<< "inside cartdata"<< inCartStr;
    return inCartStr;
}



void CartData::addDish(int dishId, QString& dishName, double dishPrice) {
    QList<QPair<QString, double>> tempDish;
    priceList.push_back(QPair<int, double>(dishId, dishPrice));
//    tempDish.push_back(QPair<QString, double>(QString::number(dishId), 0));
    tempDish.push_back(QPair<QString, double>(dishName, dishPrice));
    inCart.push_back(tempDish);
}

void CartData::addProperties(QList<QPair<QString, double>>& properties) {
    inCart.last().append(properties);
    for (auto& p : properties ) {
        priceList.last().second += p.second;
    }
    sumInCart += priceList.last().second;
}

QPair<int, QPair<QString, double>> CartData::removeDishFromCart(int index){
    QList<QPair<QString, double>> tempDish = inCart.takeAt(index);
//    CartData::GetInstance()->getCart().removeAt(index);
    QPair<int, double> tempPrice = priceList.takeAt(index);
//    CartData::GetInstance()->getPriceList().removeAt(index);
    sumInCart -= tempPrice.second;
    QPair<int, QPair<QString, double>> temp;
    temp.first = tempPrice.first;
    temp.second = tempDish.at(0);
    return temp;
}

//void Cart::updateDishInCart(int index, QMap<QString, double>& newProperties, double tempSum) {
//    QMap<QString, double> temp = removeDishFromCart(index);
//    addDishToCart(temp.begin());
//    addPropertiesToCart(newProperties, tempSum);
//}
void CartData::clearCart(){
    inCart.clear();
    priceList.clear();
    sumInCart = 0;
}

//removeLast()
