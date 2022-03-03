#include "restaurant.h"
#include "ui_restaurant.h"
#include "initdb.h"
#include "dishlist.h"

#include <QtSql>
#include <QtWidgets>

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

    // Create the data model:
    model = new QSqlRelationalTableModel(ui->restaurantTable);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setTable("authors");

    // Remember the indexes of the columns:
//    authorIdx = model->fieldIndex("author");
//    genreIdx = model->fieldIndex("genre");

    // Set the relations to the other database tables:
//    model->setRelation(authorIdx, QSqlRelation("authors", "id", "name"));
//    model->setRelation(genreIdx, QSqlRelation("genres", "id", "name"));

    // Set the localized header captions:
    model->setHeaderData(model->fieldIndex("author"), Qt::Horizontal, tr("Author Name"));
    model->setHeaderData(model->fieldIndex("birthdate"), Qt::Horizontal, tr("Birth Date"));

//    model->setHeaderData(authorIdx, Qt::Horizontal, tr("Author Name"));
//    model->setHeaderData(genreIdx, Qt::Horizontal, tr("Genre"));
//    model->setHeaderData(model->fieldIndex("title"),
//                         Qt::Horizontal, tr("Title"));
//    model->setHeaderData(model->fieldIndex("year"), Qt::Horizontal, tr("Year"));
//    model->setHeaderData(model->fieldIndex("rating"),
//                         Qt::Horizontal, tr("Rating"));

    // Populate the model:
    if (!model->select()) {
        return;
    }

    // Set the model and hide the ID column:
    ui->restaurantTable->setModel(model);
    ui->restaurantTable->setColumnHidden(model->fieldIndex("id"), true);
    ui->restaurantTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->restaurantTable->setCurrentIndex(model->index(0, 0));

    // 下面这样不太妥，参考一下 https://www.youtube.com/watch?v=fNTnU7mMgK4
    // QCheckBox *dynamic = new QCheckBox("This is a check box");
    // dynamic->show();
}

Restaurant::~Restaurant()
{
    delete ui;
}

void Restaurant::on_pushButton_clicked()
{
    int selected_row = ui->restaurantTable->currentIndex().row();
    int selected_dish_id = model->record(selected_row).field("id").value().toInt();
    dish_list_window=new DishList(this, selected_dish_id);
    this->setEnabled(false);
    dish_list_window->show();
}
