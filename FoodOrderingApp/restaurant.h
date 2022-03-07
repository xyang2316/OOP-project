#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <QMainWindow>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class Restaurant; }
QT_END_NAMESPACE

class DishList;
class Restaurant : public QMainWindow
{
    Q_OBJECT
    friend class DishList;
public:
    Restaurant(QWidget *home_window, QWidget *parent = nullptr);
    ~Restaurant();

private slots:
    void on_pushButton_clicked();
    void on_restaurantTable_clicked(const QModelIndex &index);
    void on_pushButton_home_clicked();

private:
    Ui::Restaurant *ui;
    DishList *dish_list_window;
    QSqlQueryModel  *model;
    QWidget *home_window;
};
#endif // RESTAURANT_H
