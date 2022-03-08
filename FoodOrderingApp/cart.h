#ifndef CART_H
#define CART_H

#include <QMainWindow>
#include <QMap>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class Cart; }
QT_END_NAMESPACE

class Cart : public QMainWindow
{
    Q_OBJECT
public:
    explicit Cart(QMap<QString, QWidget*> pointerStack, int restaurant_id, QWidget *parent = nullptr);
    ~Cart();

//    FUNCTIONS go to singleton:
//    void addDishToCart(QMap<QString, double>);
//    void addPropertiesToCart(QMap<QString, double>&, double);
//    QMap<QString, double> removeDishFromCart(int);
//    void updateDishInCart(int, QMap<QString, double>&, double);
//    void clearCart();


private slots:
    void on_goBackButton_clicked();
    void on_updateDishButton_clicked();
    void on_deleteButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Cart *ui;
    QWidget *dish_list_window;
    QWidget *payment_window;
    int restaurant_id;
    QMap<QString, QWidget*> pointerStack;
};

#endif // CART_H




//#include <iostream>
//#include <thread>
//#include <QString>
// //using namespace std;

//class Cart
//{
//protected:
//    Cart(int value): value_(value){}
//    static Cart* cart_;
//    int value_;

//public:
//    Cart(Cart &other) = delete;
//    void operator=(const Cart &) = delete;
//    static Cart *GetInstance(int);
//    void SomeBusinessLogic(){
//        // ...
//    }
//    int value() const{ return value_; }
//};

//Cart* Cart::cart_= nullptr;;
//Cart *Cart::GetInstance(int value)
//{
//    if(cart_==nullptr){
//        cart_ = new Cart(value);
//    }
//    return cart_;
//}


//dish name        total :
//    - size, protein...
//    - addon:...

//outer list : cart
//     inner list : dish
//            pair : attribute, price
