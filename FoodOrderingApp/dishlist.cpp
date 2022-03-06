#include "dishlist.h"
#include "ui_dishlist.h"
#include "dish.h"
#include "cart.h"
#include "cartdata.h"

#include <string>
#include <QString>
//#include <QtSql>
//#include <QtWidgets>

DishList::DishList(QWidget *retaurant_window, int restaurant_id, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DishList)
{
    this->retaurant_window = retaurant_window;
    ui->setupUi(this);
    this->restaurant_id = restaurant_id;

    this->dish_model = new QSqlQueryModel();
    dish_model->setQuery("Select * from Dish where r_id =" + QString::number(restaurant_id));
    ui->dishListTable->setModel(dish_model);




//     Create the data model:
//    dish_model = new QSqlRelationalTableModel(ui->dishListTable);
//    dish_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//    dish_model->setTable("books");

    // Set the relations to the other database tables:
//    dish_model->setRelation(dish_model->fieldIndex("author"), QSqlRelation("authors", "id", "name"));
//    dish_model->setRelation(dish_model->fieldIndex("genre"), QSqlRelation("genres", "id", "name"));

//    dish_model->setHeaderData(dish_model->fieldIndex("genre"), Qt::Horizontal, tr("Genre"));
//    dish_model->setHeaderData(dish_model->fieldIndex("title"),
//                         Qt::Horizontal, tr("Title"));
//    dish_model->setHeaderData(dish_model->fieldIndex("price"), Qt::Horizontal, tr("Price"));
//    dish_model->setHeaderData(dish_model->fieldIndex("rating"),
//                         Qt::Horizontal, tr("Rating"));

    // Populate the model:
//    std::string query = "author = " + std::to_string(restaurant_id);
//    dish_model->setFilter(query.c_str());
//    if (!dish_model->select()) {
//        return;
//    }
//    // Set the model and hide the ID column:
//    ui->dishListTable->setModel(dish_model);
//    ui->dishListTable->setColumnHidden(dish_model->fieldIndex("id"), true);
    ui->dishListTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->dishListTable->setCurrentIndex(dish_model->index(0, 0));

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
    int selected_dish_id = dish_model->record(selected_row).field("id").value().toInt();
    QString selected_dish_name = dish_model->record(selected_row).field("dish_name").value().toString();
    double selected_dish_price = dish_model->record(selected_row).field("price").value().toDouble();

    CartData::GetInstance()->addDish(selected_dish_id, selected_dish_name, selected_dish_price);
    qDebug() << CartData::GetInstance()->getPriceList();
    qDebug() << CartData::GetInstance()->getCart();

    dish_window=new Dish(this, selected_dish_id, selected_dish_price, restaurant_id);
    this->setEnabled(false);
    dish_window->show();
}

void DishList::on_viewCartButton_clicked()
{
    cart_window = new Cart(this, restaurant_id);
    this->setEnabled(false);
    cart_window->show();

}

