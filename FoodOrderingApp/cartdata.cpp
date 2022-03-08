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
    for (auto& dishList: inCart)
    {
        inCartStr += "Dish " + QString::number(i) + ": ";
        for(auto& eachPair:dishList)
        {
            inCartStr += eachPair.first + " ";
            inCartStr += "$" + QString::number(eachPair.second) + ", ";
        }
        inCartStr += "; ";
        i ++;
    }
    return inCartStr;
}



void CartData::addDish(int dishId, QString& dishName, double dishPrice) {
    QList<QPair<QString, double>> tempDish;
    priceList.push_back(QPair<int, double>(dishId, dishPrice));
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
    QPair<int, double> tempPrice = priceList.takeAt(index);
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
