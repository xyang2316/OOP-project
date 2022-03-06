#include "payment.h"
#include "ui_payment.h"
#include <QGroupBox>
#include "cartdata.h"
#include <QLabel>
#include <QtSql>
#include <QMessageBox>

Payment::Payment(QWidget *cart_window, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Payment)
{
    this->cart_window = cart_window;
    ui->setupUi(this);

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>( ui->verticalLayout->layout());
    QString sumDisplay = "Pay: $";
    sumDisplay += QString::number(CartData::GetInstance()->getSumInCart(),'f',2);
    QLabel* sum = new QLabel(sumDisplay);

    //get balance from DB
    QSqlQuery query("SELECT * FROM wallet where w_id = 1");//hard coded for now
    double accountbalance = query.record().indexOf("balance");
    double bValue=0.0;
    if (query.next())
    {
       bValue = query.value(accountbalance).toFloat();
       qDebug() << bValue;
    }
    QString balanceDisplay = "wallet: $";
    balanceDisplay += QString::number(bValue);
    QLabel* balance = new QLabel(balanceDisplay);
    layout->addWidget(sum);
    layout->addWidget(balance);
    sumToPay = CartData::GetInstance()->getSumInCart();
    walletBalance = bValue;
}

Payment::~Payment()
{
    delete ui;
}

void Payment::on_pushButton_addBalance_clicked()
{
    QString walletId, refillAmount;
    walletId = ui->lineEdit_wid->text();
    refillAmount=ui->lineEdit_payAmount->text();
////    qDebug()<< walletId;
////    qDebug()<< refillAmount;
////    createDBConnection();
//    if (!db.open()){
//        qDebug()<<"db not open!";
//        return;
//    }
    QSqlQuery qry;
    double newBalance = walletBalance + refillAmount.toDouble();
    QString newBalanceStr = QString::number(newBalance);
    QSqlQuery query("update Wallet SET balance="+ newBalanceStr +"where w_id =" + walletId);
    qDebug()<< "new amount"<<newBalanceStr;

//    if (qry.exec("select balance from wallet where wid='"+ walletId +"'"))
//    {
//        float balance = qry.exec("select balance from wallet where wid='"+ walletId +"'");
//        qDebug()<<"balance"<< balance;
//        int count=0;
//        while(qry.next())
//        {
//            count++;
//        }
//        if (count == 1)
//        {
//            //update balance in table
//            ui->label->setText("correct wid");
//        }
//        if (count < 1)
//        {
//            ui->label->setText("Wrong wallet id! Please try again.");
//        }
//    }

}



void Payment::on_pushButton_backToCart_clicked()
{
    this->cart_window->setEnabled(true);
    this->close();
}


void Payment::on_pushButton_clicked()
{
    //    if sum < balance:
    //        add order to db
    //        update db with new balance
    //    else:
    //        display a message box to remind user add money.
        if (sumToPay <= walletBalance)
        {
            QMessageBox msg;
            msg.setText(QStringLiteral("We got your order!"));
            msg.setWindowTitle(QStringLiteral("Payment success！"));
            msg.exec();
            double newBalance = walletBalance - sumToPay;
            QString newBalanceStr = QString::number(newBalance);
            QSqlQuery query("update Wallet SET balance="+ newBalanceStr +"where w_id = 1");
            qDebug()<< "order success: new balance"<<newBalanceStr;
        }
        else
        {
            QMessageBox msg;
            msg.setText(QStringLiteral("Your wallet balance is low, Please add."));
            msg.setWindowTitle(QStringLiteral("Payment fail！"));
            msg.exec();
        }
}

