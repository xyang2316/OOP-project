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
    explicit Cart(QWidget *dish_list_window, int restaurant_id, QWidget *parent = nullptr);
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
};

#endif // CART_H
