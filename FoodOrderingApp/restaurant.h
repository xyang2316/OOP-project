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
    Restaurant(QWidget *parent = nullptr);
    ~Restaurant();
    //for debug
    QSqlDatabase mydb;

private slots:
    void on_pushButton_clicked();

    void on_restaurantTable_clicked(const QModelIndex &index);

private:
    Ui::Restaurant *ui;
//    QSqlRelationalTableModel *model;
    DishList *dish_list_window;
    QSqlQueryModel  *model;
//    QSqlTableModel  *model;
};
#endif // RESTAURANT_H
