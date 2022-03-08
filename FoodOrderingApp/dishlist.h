#ifndef DISHLIST_H
#define DISHLIST_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {class DishList;}

class Dish;
class Cart;
class DishList : public QMainWindow
{
    Q_OBJECT
    friend class Dish;
    friend class Cart;
public:
//    explicit DishList(QWidget *retaurant_window, int restaurant_id, QWidget *parent = nullptr);
    explicit DishList(QMap<QString, QWidget*>, int restaurant_id, QWidget *parent = nullptr);

    ~DishList();

private slots:
    void on_reselectRestaurantButton_clicked();
    void on_updateDishButton_clicked();
    void on_viewCartButton_clicked();

    void on_dishListTable_clicked(const QModelIndex &index);

private:
    Ui::DishList *ui;
    QWidget *retaurant_window;
//    QSqlRelationalTableModel *dish_model;
    Dish *dish_window;
    Cart *cart_window;
    int restaurant_id;
    QSqlQueryModel *dish_model;
    QMap<QString, QWidget*> pointerStack;
};

#endif // DISHLIST_H

//QMap<QString, QWidget*>
