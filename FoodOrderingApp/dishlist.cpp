#include "dishlist.h"
#include "ui_dishlist.h"
#include "dish.h"
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

//     Create the data model:
    dish_model = new QSqlRelationalTableModel(ui->dishListTable);
    dish_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    dish_model->setTable("books");

    // Set the relations to the other database tables:
    dish_model->setRelation(dish_model->fieldIndex("author"), QSqlRelation("authors", "id", "name"));
    dish_model->setRelation(dish_model->fieldIndex("genre"), QSqlRelation("genres", "id", "name"));

    // Set the localized header captions:
 //    model->setHeaderData(model->fieldIndex("author"), Qt::Horizontal, tr("Author Name"));
 //    model->setHeaderData(model->fieldIndex("birthdate"), Qt::Horizontal, tr("Birth Date"));

 //    model->setHeaderData(authorIdx, Qt::Horizontal, tr("Author Name"));
    dish_model->setHeaderData(dish_model->fieldIndex("genre"), Qt::Horizontal, tr("Genre"));
    dish_model->setHeaderData(dish_model->fieldIndex("title"),
                         Qt::Horizontal, tr("Title"));
    dish_model->setHeaderData(dish_model->fieldIndex("price"), Qt::Horizontal, tr("Price"));
    dish_model->setHeaderData(dish_model->fieldIndex("rating"),
                         Qt::Horizontal, tr("Rating"));

    // Populate the model:
    std::string query = "author = " + std::to_string(restaurant_id);
    dish_model->setFilter(query.c_str());
    if (!dish_model->select()) {
        return;
    }
    // Set the model and hide the ID column:
    ui->dishListTable->setModel(dish_model);
    ui->dishListTable->setColumnHidden(dish_model->fieldIndex("id"), true);
    ui->dishListTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->dishListTable->setCurrentIndex(dish_model->index(0, 0));

}

DishList::~DishList()
{
    delete ui;
}

void DishList::on_reselectRestaurantButton_clicked()
{
    this->retaurant_window->setEnabled(true);
    this->close();
}

void DishList::on_updateDishButton_clicked()
{
    int selected_row = ui->dishListTable->currentIndex().row();
    int selected_dish_id = dish_model->record(selected_row).field("id").value().toInt();
    dish_window=new Dish(this, selected_dish_id);
    this->setEnabled(false);
    dish_window->show();
}


void DishList::on_viewCartButton_clicked()
{
//    global_cart->show();
 //    this->setEnabled(false);
 //    this->close();

}

