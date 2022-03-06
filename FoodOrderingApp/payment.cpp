#include "payment.h"
#include "ui_payment.h"
#include <QGroupBox>
#include "cartdata.h"
#include <QLabel>

Payment::Payment(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Payment)
{
    ui->setupUi(this);

    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>( ui->verticalLayout->layout());
    QString sumDisplay = "Pay: $";
    sumDisplay += QString::number(CartData::GetInstance()->getSumInCart(),'f',2);
    QString accountBalance = "wallet: $";
    QLabel* sum = new QLabel(sumDisplay);
    //get balance from DB
    QLabel* balance = new QLabel(accountBalance);
    layout->addWidget(sum);
    layout->addWidget(balance);
}

Payment::~Payment()
{
    delete ui;
}

void Payment::on_pushButton_clicked()
{
//    if sum < balance:
//        add order to db
//    else:
//        display a message box to remind user add money.

}


void Payment::on_pushButton_2_clicked()
{
//    QString walletId, refillAmount;
//    walletId = ui->lineEdit_wid->text();
//    refillAmount=ui->lineEdit_payAmount->text();
////    qDebug()<< walletId;
////    qDebug()<< refillAmount;
////    createDBConnection();
//    if (!db.open()){
//        qDebug()<<"db not open!";
//        return;
//    }
//    QSqlQuery qry;
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

