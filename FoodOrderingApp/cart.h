#ifndef CART_H
#define CART_H

#include <QMainWindow>
#include <QMap>
#include <QList>

//namespace Ui {
//class Cart;
//}

//class Cart : public QMainWindow
//{
//    Q_OBJECT

//public:
//    explicit Cart(QWidget *parent = nullptr);
//    ~Cart();
////    void addDishToCart(QMap<QString, double>);
////    void addPropertiesToCart(QMap<QString, double>&, double);
////    QMap<QString, double> removeDishFromCart(int);
////    void updateDishInCart(int, QMap<QString, double>&, double);


////    void clearCart();



//private:
//    Ui::Cart *ui;
//    QList<QMap <QString, double> >* inCart;
//    double sumInCart = 0.0;
//};


#include <iostream>
#include <thread>
#include <QString>
//using namespace std;

class Cart
{
protected:
    Cart(int value): value_(value){}
    static Cart* cart_;
    int value_;

public:
    Cart(Cart &other) = delete;
    void operator=(const Cart &) = delete;
    static Cart *GetInstance(int);
    void SomeBusinessLogic(){
        // ...
    }
    int value() const{ return value_; }
};

Cart* Cart::cart_= nullptr;;
Cart *Cart::GetInstance(int value)
{
    if(cart_==nullptr){
        cart_ = new Cart(value);
    }
    return cart_;
}
#endif // CART_H


//dish name        total :
//    - size, protein...
//    - addon:...

//outer list : cart
//     inner list : dish
//            pair : attribute, price
