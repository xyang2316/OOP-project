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


Cart::Cart(QWidget *dish_list_window, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Cart)
{
    this->dish_list_window = dish_list_window;
    ui->setupUi(this);

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>( ui->verticalLayout->layout());

//    layout->addStretch();
//    layout->setDirection(QVBoxLayout::TopToBottom);

    QGroupBox *groupbox = new QGroupBox(tr("Order Summary:"));
    layout->addWidget(groupbox);
//        layout->setDirection(QVBoxLayout::TopToBottom);
//    QList<QString>
    QVBoxLayout *vbox = new QVBoxLayout;
//    qDebug() << CartData::GetInstance()->getCart().size();
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
//        qDebug() << label->text();
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
    int dishIndex = NULL;
    for(int i = 0; i < allButtons.size(); ++i){
        if(allButtons.at(i)->isChecked()) {
//            QList tempProp = allButtons.at(i)->text().split(QLatin1String(" : $ "));
//            choices.push_back(QPair<QString, double>(title.append(" : ").append(tempProp[0]), tempProp[1].toDouble()));
            dishIndex = i;
        }
    }
    QPair<int, QPair<QString, double>> temp = CartData::GetInstance()->removeDishFromCart(dishIndex);
    int dishId = temp.first;
    QString dishName = temp.second.first;
    double dishPrice = temp.second.second;
    CartData::GetInstance()->addDish(dishId,dishName, dishPrice);
    Dish* newDish_window = new Dish(this, dishId, dishPrice);
    newDish_window->show();
    this->close();


}

void Cart::on_deleteButton_clicked()
{
    QList<QRadioButton *> allButtons = ui->centralwidget->findChildren<QRadioButton *>();
    int dishIndex;
    for(int i = 0; i < allButtons.size(); ++i){
        if(allButtons.at(i)->isChecked()) {
            dishIndex = i;
        }
    }
    CartData::GetInstance()->removeDishFromCart(dishIndex);
    qDebug() << CartData::GetInstance()->getPriceList();
    qDebug() << CartData::GetInstance()->getSumInCart();

    this->dish_list_window->setEnabled(true);
    this->close();

}


void Cart::on_pushButton_2_clicked()
{
    payment_window = new Payment(this);
    this->setEnabled(false);
    payment_window->show();
}

