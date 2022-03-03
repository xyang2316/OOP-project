#ifndef DISH_H
#define DISH_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class Dish;
}

class Dish : public QMainWindow
{
    Q_OBJECT

public:
    explicit Dish(QWidget *dish_list_window, int dish_id, QWidget *parent = nullptr);
    ~Dish();

private slots:
    void on_goBackButton_clicked();

private:
    Ui::Dish *ui;
    QWidget *dish_list_window;
    QSqlRelationalTableModel *property_model;
    int dish_id;
};

#endif // DISH_H
