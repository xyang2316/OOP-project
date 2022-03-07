#ifndef CARTDATA_H
#define CARTDATA_H
#include <QString>
#include <QList>
#include <QPair>

class CartData
{
public:
    CartData(CartData &other) = delete;
    void operator=(const CartData &) = delete;
    static CartData *GetInstance();

    QList<QPair<int, double>> getPriceList();
    QList<QList<QPair<QString, double>>> getCart();
    QString getInCartStr();
    double getSumInCart();

    void addDish(int, QString&, double);
    void addProperties(QList<QPair<QString, double>>&);
    QPair<int, QPair<QString, double>> removeDishFromCart(int);
    void clearCart();

//    ~Cart();
protected:
    CartData();
    static CartData* cartData_;
    double sumInCart;
    QList<QList<QPair<QString, double>>> inCart;
    QList<QPair<int, double>> priceList;
    QString inCartStr;

};

#endif // CARTDATA_H
