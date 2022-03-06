#include "restaurant.h"
#include "ui_restaurant.h"
#include "initdb.h"
#include "dishlist.h"

#include <QtSql>
#include <QtWidgets>
#include <QtCore>
#include <QtGui>

Restaurant::Restaurant(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Restaurant)
{
    ui->setupUi(this);

    if (!QSqlDatabase::drivers().contains("QSQLITE")) {return;}

    // Initialize the database:
    QSqlError err = initDb();
    if (err.type() != QSqlError::NoError) {
        return;
    }

//    QSqlQuery query(db);
//    query.exec("select * from Restaurant");
//    while(query.next()){
//        qDebug()<<query.value(1).toString();
//    }

    this->model = new QSqlQueryModel();
    model->setQuery("Select * from Restaurant");
    ui->restaurantTable->setModel(model);






    // Create the data model:
//    model = new QSqlRelationalTableModel(ui->restaurantTable);
//    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//    model->setTable("authors");

//    // Set the localized header captions:
//    model->setHeaderData(model->fieldIndex("author"), Qt::Horizontal, tr("Author Name"));
//    model->setHeaderData(model->fieldIndex("birthdate"), Qt::Horizontal, tr("Birth Date"));

//    // Populate the model:
//    if (!model->select()) {
//        return;
//    }

//    // Set the model and hide the ID column:
//    ui->restaurantTable->setModel(model);
//    ui->restaurantTable->setColumnHidden(model->fieldIndex("id"), true);
//    ui->restaurantTable->setSelectionMode(QAbstractItemView::SingleSelection);
//    ui->restaurantTable->setCurrentIndex(model->index(0, 0));
}

Restaurant::~Restaurant()
{
    delete ui;
//    closeDB();
}

void Restaurant::on_pushButton_clicked()
{
    int selected_row = ui->restaurantTable->currentIndex().row();
    int selected_dish_id = model->record(selected_row).field("id").value().toInt();
    dish_list_window=new DishList(this, selected_dish_id);
    this->setEnabled(false);
    dish_list_window->show();
}
