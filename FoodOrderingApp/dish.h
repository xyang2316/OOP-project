#ifndef DISH_H
#define DISH_H

#include <QMainWindow>
#include <QtSql>
#include <QList>

namespace Ui {
class Dish;
}

class Dish : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dish(QWidget *dish_list_window, int dish_id, double dish_price, QWidget *parent = nullptr);
    ~Dish();

private slots:
    void on_goBackButton_clicked();
//    bool calculate(double rightOperand, const QString &pendingOperator);
    void on_confirmButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::Dish *ui;
    QWidget *dish_list_window;
    QSqlRelationalTableModel *property_model;
    int dish_id;
//    QList<QList<QString>> memory;
    double dishSum;
    QWidget *payment_window;
};

#endif // DISH_H
