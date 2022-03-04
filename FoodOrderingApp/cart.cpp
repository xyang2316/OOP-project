//#include "cart.h"
//#include "ui_cart.h"

//Cart::Cart(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::Cart)
//{
//    ui->setupUi(this);

//}

//Cart::~Cart()
//{
//    delete ui;
//}

//void Cart::addDishToCart(QMap<QString, double> dish){
//    inCart->push_back(dish);
//}
//void Cart::addPropertiesToCart(QMap<QString, double>& properties, double dishSum) {
//    inCart->last().insert(properties);
//    sumInCart += dishSum;
//}
//QMap<QString, double> Cart::removeDishFromCart(int index){
//    QMap<QString, double> temp = inCart->at(index);
//    inCart->remove(index);
//    foreach (const double value, temp.values()) {
//        sumInCart -= value;
//    }
//    return temp;
//}
//void Cart::updateDishInCart(int index, QMap<QString, double>& newProperties, double tempSum) {
//    QMap<QString, double> temp = removeDishFromCart(index);
//    addDishToCart(temp.begin());
//    addPropertiesToCart(newProperties, tempSum);
//}
//void Cart::clearCart(){
//    inCart->clear();
//    sumInCart = 0;
//}

//removeLast()
