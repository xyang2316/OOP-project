#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "restaurant.h"


extern QVector<Restaurant>restaurantList;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    ui->RestaurantTableWidget->setColumnCount(2);
    ui->RestaurantTableWidget->setRowCount(0);
    ui->RestaurantTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(QStringLiteral("rid")) );
    ui->RestaurantTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(QStringLiteral("rname")) );
    qDebug() << restaurantList.size();
    for(int i=0;i<restaurantList.size();i++){
//        qDebug() << i;
//        qDebug() << restaurantList[i].getId();
//        qDebug() << "end";
        ui->RestaurantTableWidget->setRowCount(i+1);
        ui->RestaurantTableWidget->setItem(i,0,new QTableWidgetItem(restaurantList[i].getId()));
        ui->RestaurantTableWidget->setItem(i,1,new QTableWidgetItem(restaurantList[i].getName()));
    }
}

