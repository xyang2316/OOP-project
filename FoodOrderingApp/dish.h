#ifndef DISH_H
#define DISH_H

#include <QMainWindow>
#include <QtSql>
#include <QList>

namespace Ui {
class Dish;
}
class Cart;
class Dish : public QMainWindow
{
    Q_OBJECT
    friend class Cart;
public:
    explicit Dish(QWidget *dish_list_window, int dish_id, double dish_price, QWidget *parent = nullptr);
    ~Dish();

private slots:
    void on_goBackButton_clicked();
//    bool calculate(double rightOperand, const QString &pendingOperator);
    void on_confirmButton_clicked();

private:
    Ui::Dish *ui;
    QWidget *dish_list_window;
    Cart *cart_window;
    QSqlRelationalTableModel *property_model;
    int dish_id;
//    QList<QList<QString>> memory;
    double dishSum;
};

#endif // DISH_H
