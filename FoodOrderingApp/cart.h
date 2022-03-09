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

private slots:
    void on_goBackButton_clicked();
    void on_updateDishButton_clicked();
    void on_deleteButton_clicked();
    void on_pushButton_toPayment_clicked();

private:
    Ui::Cart *ui;
    QWidget *dish_list_window;
    QWidget *payment_window;
    int restaurant_id;
    QMap<QString, QWidget*> pointerStack;
};

#endif // CART_H
