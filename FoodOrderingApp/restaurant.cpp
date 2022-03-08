#include "restaurant.h"
#include "ui_restaurant.h"
#include "dishlist.h"
#include "homepage.h"
#include <QtSql>
#include <QtWidgets>
#include <QtCore>
#include <QtGui>

Restaurant::Restaurant(QMap<QString, QWidget*> pointerStack, QWidget *parent)

    : QMainWindow(parent)
    , ui(new Ui::Restaurant)
{
    this->pointerStack = pointerStack;
    this->home_window = pointerStack["Homepage"];
    ui->setupUi(this);
    this->model = new QSqlQueryModel();

    model->setQuery("Select r_id, r_name from Restaurant");
    ui->restaurantTable->setModel(model);
    ui->restaurantTable->setColumnWidth(0, 50);
    ui->restaurantTable->setColumnWidth(1, 400);
    ui->restaurantTable->setColumnHidden(0, true);
    model->setHeaderData(1, Qt::Horizontal, tr("Restaurant Name"));
    ui->restaurantTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->restaurantTable->setCurrentIndex(model->index(0, 0));
}

Restaurant::~Restaurant()
{
    delete ui;
}

void Restaurant::on_pushButton_clicked()
{
    int selected_row = ui->restaurantTable->currentIndex().row();
    qDebug()<<"selected_row in restaurant: "<<selected_row;
    int selected_restaurant_id = model->record(selected_row).field("r_id").value().toInt();
    qDebug()<<"selected_rid in restaurant: "<<selected_restaurant_id;
    pointerStack["Restaurant"] = this;
    dish_list_window=new DishList(pointerStack, selected_restaurant_id);

    this->setEnabled(false);
    dish_list_window->show();
}

void Restaurant::on_restaurantTable_clicked(const QModelIndex &index)
{
//    qDebug()<<"click"<<index;
}


void Restaurant::on_pushButton_home_clicked()
{
    this->home_window->setEnabled(true);
    this->close();
}

