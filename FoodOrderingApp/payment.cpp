#include "payment.h"
#include "ui_payment.h"
#include <QGroupBox>
#include "cartdata.h"
#include <QLabel>
#include <QtSql>
#include <QMessageBox>

Payment::Payment(QWidget *cart_window, int restaurant_id, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Payment)
{
    this->cart_window = cart_window;
    this->restaurant_id = restaurant_id;
    ui->setupUi(this);

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>( ui->verticalLayout->layout());
    QString sumDisplay = "Pay: $";
    sumDisplay += QString::number(CartData::GetInstance()->getSumInCart(),'f',2);
    QLabel* sum = new QLabel(sumDisplay);
    layout->addWidget(sum);
    sumToPay = CartData::GetInstance()->getSumInCart();
    walletBalance = getWalletBalance();
}

Payment::~Payment()
{
    delete ui;
}

void Payment::on_pushButton_addBalance_clicked()
{
    QString refillAmount;
    refillAmount=ui->lineEdit_payAmount->text();

    QSqlQuery qry;
    double newBalance = walletBalance + refillAmount.toDouble();
    QString newBalanceStr = QString::number(newBalance);
    qry.prepare("update Wallet SET balance='"+ newBalanceStr +"' where w_id = 1");
    if (qry.exec()){
        qDebug()<< "add$ success: new balance"<<newBalanceStr;
        QMessageBox msg;
        msg.setText("Successfully added $" + refillAmount + " to your e-wallet!");
        msg.setWindowTitle(QStringLiteral("Payment success！"));
        msg.exec();
    }
    else{
        qDebug()<<"add$ fail"<<qry.lastError();
        QMessageBox msg;
        msg.setText(qry.lastError().text());
        msg.setWindowTitle(QStringLiteral("Payment failed！"));
        msg.exec();
    }
    qDebug()<< "new amount"<<newBalanceStr;
}



void Payment::on_pushButton_backToCart_clicked()
{
    this->cart_window->setEnabled(true);
    this->close();
}


void Payment::on_pushButton_clicked()
{
    walletBalance = getWalletBalance();
    if (sumToPay <= walletBalance)
    {
        QMessageBox msg;
        msg.setText(QStringLiteral("We got your order!"));
        msg.setWindowTitle(QStringLiteral("Payment success！"));
        msg.exec();
        double newBalance = walletBalance - sumToPay;
        QString newBalanceStr = QString::number(newBalance);
        QSqlQuery qry;
        qry.prepare("update Wallet SET balance='"+ newBalanceStr +"' where w_id = 1");//hard code
        if (qry.exec()){
            qDebug()<< "order success: new balance"<<newBalanceStr;
        }
        else{
            qDebug()<<"order fail"<<qry.lastError();
        }
        //insert to order
        QDateTime date = QDateTime::currentDateTime();
        QString formattedTime = date.toString("dd.MM.yyyy hh:mm:ss");
        QString inCartStr = CartData::GetInstance()->getInCartStr();
        qDebug()<< "incart string"<<inCartStr;
        insertOrder(formattedTime, sumToPay, restaurant_id, inCartStr);
        CartData::GetInstance()->clearCart();
    }
    else
    {
        QMessageBox msg;
        msg.setText(QStringLiteral("Your wallet balance is low, Please add."));
        msg.setWindowTitle(QStringLiteral("Payment fail！"));
        msg.exec();
    }
}

void Payment::insertOrder(QString oid, float sumPaid, int rid, QString dishesInfo)
{
    //insert to order
    QSqlQuery qry;
    qry.prepare("INSERT INTO Orders(o_id, paid, r_id, d_info) VALUES(?,?,?,?);");
    qry.addBindValue(oid);
    qry.addBindValue(sumPaid);
    qry.addBindValue(rid);
    qry.addBindValue(dishesInfo);
    qDebug()<<oid <<sumPaid << rid << dishesInfo;
    if (qry.exec()){
        qDebug()<< "order saved";
    }
    else{
        qDebug()<<"order save fail"<<qry.lastError();
    }
}


void Payment::on_pushButton_checkBalance_clicked()
{
    QString balanceDisplay = "Your Balance: $";
    float bValue = getWalletBalance();
    QString bValueStr = QString::number(bValue);
    balanceDisplay += bValueStr;
    walletBalance = bValue;

    QMessageBox msg;
    msg.setText(balanceDisplay);
    msg.setWindowTitle(QStringLiteral("Check balance"));
    msg.exec();
}

float Payment::getWalletBalance()
{
    QSqlQuery query("SELECT * FROM wallet where w_id = 1");
    double accountbalance = query.record().indexOf("balance");
    double bValue=-1.0;
    if (query.next())
    {
       bValue = query.value(accountbalance).toFloat();
       walletBalance = bValue;
       qDebug() << bValue;
    }
    return walletBalance;
}




void Payment::on_pushButton_home_clicked()
{
    //TODO
    this->close();
    cart_window->close();
    CartData::GetInstance()->clearCart();
}

