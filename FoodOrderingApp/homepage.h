#ifndef HOMEPAGE_H
#define HOMEPAGE_H
#include "restaurant.h"
#include <QMainWindow>

namespace Ui {
class HomePage;
}

class HomePage : public QMainWindow
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

private slots:
    void on_pushButton_orderNow_clicked();
    void on_pushButton_checkBalance_clicked();
    void on_pushButton_addBalance_clicked();
    void on_pushButton_orderHistory_clicked();

private:
    Ui::HomePage *ui;
    Restaurant *restaurant_window;
    QSqlQueryModel  *model;
};

#endif // HOMEPAGE_H
