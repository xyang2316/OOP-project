#include "dishlist.h"
#include "ui_dishlist.h"
#include "dish.h"
#include "cart.h"
#include "cartdata.h"
#include "numberformatdelegate.h"
#include <string>
#include <QString>

DishList::DishList(QMap<QString, QWidget*> pointerStack, int restaurant_id, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DishList)
{
    this->pointerStack = pointerStack;
    this->retaurant_window = pointerStack["Restaurant"];
    ui->setupUi(this);
    this->restaurant_id = restaurant_id;
    this->dish_model = new QSqlQueryModel();
    dish_model->setQuery("Select dish_id, dish_name, price, d_type from Dish where r_id =" + QString::number(restaurant_id));
    qDebug()<<"rid"<<QString::number(restaurant_id);

    dish_model->setHeaderData(1, Qt::Horizontal, tr("Dish Name"));
    dish_model->setHeaderData(2, Qt::Horizontal, tr("Price($)"));
    dish_model->setHeaderData(3, Qt::Horizontal, tr("Dish Type"));
    ui->dishListTable->setModel(dish_model);

    ui->dishListTable->setColumnWidth(1, 280);
    ui->dishListTable->setColumnWidth(2, 50);
    ui->dishListTable->setColumnWidth(3, 100);
    ui->dishListTable->setColumnHidden(0, true);

    ui->dishListTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->dishListTable->setCurrentIndex(dish_model->index(0, 0));

    ui->dishListTable->setItemDelegateForColumn(2, new NumberFormatDelegate(this));
}

DishList::~DishList()
{
    delete ui;
}

void DishList::on_reselectRestaurantButton_clicked()
{
    CartData::GetInstance()->clearCart();
    this->retaurant_window->setEnabled(true);
    this->close();
}

void DishList::on_updateDishButton_clicked()
{
    int selected_row = ui->dishListTable->currentIndex().row();
    int selected_dish_id = dish_model->record(selected_row).field("dish_id").value().toInt();
    QString selected_dish_name = dish_model->record(selected_row).field("dish_name").value().toString();
    double selected_dish_price = dish_model->record(selected_row).field("price").value().toDouble();

    CartData::GetInstance()->addDish(selected_dish_id, selected_dish_name, selected_dish_price);
    qDebug() << CartData::GetInstance()->getPriceList();
    qDebug() << CartData::GetInstance()->getCart();

    pointerStack["Menu"] = this;
    dish_window=new Dish(pointerStack, selected_dish_id, selected_dish_price, restaurant_id);

    this->setEnabled(false);
    dish_window->show();
}

void DishList::on_viewCartButton_clicked()
{
    pointerStack["Menu"] = this;
    cart_window = new Cart(pointerStack, restaurant_id);
    this->setEnabled(false);
    cart_window->show();
}
