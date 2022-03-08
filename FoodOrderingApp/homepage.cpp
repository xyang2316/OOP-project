#include "homepage.h"
#include "ui_homepage.h"
#include "numberformatdelegate.h"
#include "initdb.h"
#include "payment.h"
#include <QMessageBox>
#include <QInputDialog>

HomePage::HomePage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HomePage)
{
    ui->setupUi(this);
    if (!QSqlDatabase::drivers().contains("QSQLITE")) {return;}

    // Initialize the database:
    QSqlError err = initDb();
    if (err.type() != QSqlError::NoError) {
        return;
    }
}

HomePage::~HomePage()
{
    delete ui;
}

void HomePage::on_pushButton_orderNow_clicked()
{   
    QMap<QString, QWidget*> pointerStack;
    pointerStack["Homepage"] = this;
    restaurant_window = new Restaurant(pointerStack);

    this->setEnabled(false);
    restaurant_window->show();
}

void HomePage::on_pushButton_checkBalance_clicked()
{
    QString balanceDisplay = "Your Balance: $";
    QSqlQuery query("SELECT * FROM wallet where w_id = 1");
    double accountbalance = query.record().indexOf("balance");
    double bValue= 0.0;
    if (query.next())
    {
       bValue = query.value(accountbalance).toFloat();
       qDebug() << bValue;
    }
    QString bValueStr = QString::number(bValue);
    balanceDisplay += bValueStr;

    QMessageBox msg;
    msg.setText(balanceDisplay);
    msg.setWindowTitle(QStringLiteral("Check balance"));
    msg.exec();
}

void HomePage::on_pushButton_addBalance_clicked()
{
    QInputDialog dialog;
    double topupValue = dialog.getDouble(this, "Top up", "Input the amount you want to add:");
    QString topupValueStr = QString::number(topupValue);

    QSqlQuery qry;
    QSqlQuery query("SELECT * FROM wallet where w_id = 1");
    double accountbalance = query.record().indexOf("balance");
    double wBalance= -1.0;
    if (query.next())
    {
       wBalance = query.value(accountbalance).toFloat();
    }

    float newValue = wBalance + topupValue;
    QString newValueStr = QString::number(newValue);
    qry.prepare("update Wallet SET balance='"+ newValueStr +"' where w_id = 1");
    if (qry.exec()){
        QMessageBox msg;
        msg.setText("Successfully added $" + topupValueStr + " to your e-wallet!\nCurrent balance is $" + newValueStr);
        msg.setWindowTitle(QStringLiteral("Payment success！"));
        msg.exec();
    }
    else{
        qDebug()<<"Fail to add."<<qry.lastError();
        QMessageBox msg;
        msg.setText(qry.lastError().text());
        msg.setWindowTitle(QStringLiteral("Payment failed！"));
        msg.exec();
    }
    qDebug()<< "new amount in wallet"<<newValueStr;
}

void HomePage::on_pushButton_orderHistory_clicked()
{
    this->model = new QSqlQueryModel();
    model->setQuery("Select * from Orders ORDER BY o_id DESC");

    model->setHeaderData(0, Qt::Horizontal, tr("Order date"));
    model->setHeaderData(1, Qt::Horizontal, tr("Order total($)"));
    model->setHeaderData(2, Qt::Horizontal, tr("Restaurant"));
    model->setHeaderData(3, Qt::Horizontal, tr("Order detail"));
    ui->tableViewOrders->setModel(model);

    ui->tableViewOrders->setColumnWidth(0, 150);
    ui->tableViewOrders->setColumnWidth(1, 100);
    ui->tableViewOrders->setColumnWidth(2, 150);
    ui->tableViewOrders->setColumnWidth(3, 300);
    ui->tableViewOrders->setItemDelegateForColumn(1, new NumberFormatDelegate(this));//debug
}

