#include "cart.h"
#include "ui_cart.h"
#include "dish.h"
#include "cartdata.h"
#include <QList>
#include <QRadioButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include "payment.h"

Cart::Cart(QMap<QString, QWidget*> pointerStack, int restaurant_id, QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::Cart)
{
    this->pointerStack = pointerStack;
    this->dish_list_window = pointerStack["Menu"];
    this->restaurant_id = restaurant_id;
    ui->setupUi(this);

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>( ui->verticalLayout->layout());
    QGroupBox *groupbox = new QGroupBox();
    layout->addWidget(groupbox);
    QVBoxLayout *vbox = new QVBoxLayout;
    for(int i = 0; i < CartData::GetInstance()->getCart().size(); i++) {
        QList<QPair<QString, double>> sdish = CartData::GetInstance()->getCart().at(i);
        QString dishName = sdish.at(0).first;
        double dishTotalPrice = CartData::GetInstance()->getPriceList().at(i).second;
        QRadioButton* radiobutton = new QRadioButton(dishName.append(" : $").append(QString::number(dishTotalPrice, 'f',2)),ui->centralwidget);
        QString sprops = "";
        for (int j = 1; j < sdish.size(); j++) {
            sprops.append(sdish.at(j).first);
            sprops.append("\n");
        }
        QLabel* label = new QLabel(sprops);
        vbox->addWidget(radiobutton);
        vbox->addWidget(label);
    }

    groupbox->setLayout(vbox);
    QString sumDisplay = "Total: $";
    sumDisplay += QString::number(CartData::GetInstance()->getSumInCart(),'f',2);
    QLabel* sum = new QLabel(sumDisplay);
    layout->addWidget(sum);
}

Cart::~Cart()
{
    delete ui;
}

void Cart::on_goBackButton_clicked()
{
    this->dish_list_window->setEnabled(true);
    this->close();
}

void Cart::on_updateDishButton_clicked()
{
    QList<QRadioButton *> allButtons = ui->centralwidget->findChildren<QRadioButton *>();
    int dishIndex = -1;
    for(int i = 0; i < allButtons.size(); ++i){
        if(allButtons.at(i)->isChecked()) {
            dishIndex = i;
        }
    }
    if (dishIndex >= 0) {
        QPair<int, QPair<QString, double>> temp = CartData::GetInstance()->removeDishFromCart(dishIndex);
        int dishId = temp.first;
        QString dishName = temp.second.first;
        double dishPrice = temp.second.second;
        CartData::GetInstance()->addDish(dishId,dishName, dishPrice);
        pointerStack["Cart"] = this;
        Dish* newDish_window = new Dish(pointerStack, dishId, dishPrice, restaurant_id);
        newDish_window->show();
        this->close();
    }
}

void Cart::on_deleteButton_clicked()
{
    QList<QRadioButton *> allButtons = ui->centralwidget->findChildren<QRadioButton *>();
    int dishIndex = -1;
    for(int i = 0; i < allButtons.size(); ++i){
        if(allButtons.at(i)->isChecked()) {
            dishIndex = i;
        }
    }
    if (dishIndex >= 0) {
        CartData::GetInstance()->removeDishFromCart(dishIndex);
        qDebug() << CartData::GetInstance()->getPriceList();
        qDebug() << CartData::GetInstance()->getSumInCart();

        this->dish_list_window->setEnabled(true);
        this->close();
    }
}

void Cart::on_pushButton_toPayment_clicked()
{
    qDebug() << CartData::GetInstance()->getInCartStr();
    qDebug() << CartData::GetInstance()->getPriceList();
    pointerStack["Cart"] = this;
    payment_window = new Payment(pointerStack, restaurant_id);
    this->setEnabled(false);
    payment_window->show();
}

