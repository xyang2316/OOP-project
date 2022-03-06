#ifndef PAYMENT_H
#define PAYMENT_H
#include <QMainWindow>
#include "cart.h"
//#include "initdb.h"

namespace Ui {
class Payment;
}

class Payment : public QMainWindow
{
    Q_OBJECT

public:
    explicit Payment(QWidget *cart_window, QWidget *parent = nullptr);
    ~Payment();

private slots:

    void on_pushButton_addBalance_clicked();

    void on_pushButton_backToCart_clicked();

    void on_pushButton_clicked();

private:
    Ui::Payment *ui;
    QWidget *cart_window;
    double sumToPay;
    double walletBalance;
};

#endif // PAYMENT_H
