#ifndef PAYMENT_H
#define PAYMENT_H
#include <QMainWindow>
#include "cart.h"

namespace Ui {
class Payment;
}

class Payment : public QMainWindow
{
    Q_OBJECT

public:
    explicit Payment(QMap<QString, QWidget*> pointerStack, int restaurant_id, QWidget *parent = nullptr);
    ~Payment();

private slots:
    void on_pushButton_addBalance_clicked();
    void on_pushButton_backToCart_clicked();
    void on_pushButton_clicked();
    void on_pushButton_checkBalance_clicked();
    void insertOrder(QString oid, float sumPaid, int rid, QString dishesInfo);
    void on_pushButton_home_clicked();

public:
    float getWalletBalance();

private:
    Ui::Payment *ui;
    QWidget *cart_window;
    double sumToPay;
    double walletBalance;
    int restaurant_id;
    QString inCartStr;
    QMap<QString, QWidget*> pointerStack;
};

#endif // PAYMENT_H
