#ifndef CART_H
#define CART_H

#include <QMainWindow>
#include <QList>
//#include "dish.h"

namespace Ui {
class Cart;
}

class Cart : public QMainWindow
{
    Q_OBJECT

public:
    explicit Cart(QWidget *parent = nullptr);
    ~Cart();

private:
    Ui::Cart *ui;
//    QList<Dish> items_in_cart;
};

#endif // CART_H
