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

private slots:
    void on_pushButton_clicked();

private:
    Ui::Restaurant *ui;
    QSqlRelationalTableModel *model;
    DishList *dish_list_window;
};
#endif // RESTAURANT_H
