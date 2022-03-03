#include "dish.h"
#include "ui_dish.h"
#include <string>
#include <QString>
#include <iostream>
#include <QCheckBox>
#include <QRadioButton>
#include <QVBoxLayout>

Dish::Dish(QWidget *dish_list_window, int dish_id, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dish)
{
    this->dish_list_window = dish_list_window;
    ui->setupUi(this);
    this->dish_id = dish_id;

//     Create the data model:
    property_model = new QSqlRelationalTableModel();
    // property_model = new QSqlRelationalTableModel(ui->singleSelectTable);
    property_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    property_model->setTable("properties");

    // Set the relations to the other database tables:
    property_model->setRelation(property_model->fieldIndex("book"), QSqlRelation("books", "id", "title"));

    property_model->setHeaderData(property_model->fieldIndex("book"), Qt::Horizontal, tr("Dish"));
    property_model->setHeaderData(property_model->fieldIndex("property"), Qt::Horizontal, tr("Category"));
    property_model->setHeaderData(property_model->fieldIndex("propertyJSON"), Qt::Horizontal, tr("JSON"));

    // Populate the model:
//    QString query = QString("propertyTypeId = %1 AND bookId = %2").arg(1, dish_id);
    QString query = QString("book = %1").arg(dish_id);
    property_model->setFilter(query);
    if (!property_model->select()) {
        return;
    }

    // Generate checkboxes
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>( ui->verticalLayout->layout());
    for (int row = 0; row < property_model->rowCount(); row++) {
        QByteArray tempjson = property_model->record(row).field("propertyJSON").value().toByteArray();
        QJsonObject json = QJsonDocument::fromJson(tempjson).object();
        QString labelText = property_model->record(row).field("property").value().toString();
        QLabel* label = new QLabel(labelText);
        layout->addWidget(label);
        foreach(const QString& key, json.keys()) {
              QJsonValue value = json.value(key);
              QString text = QString("%1 : $%2").arg(key).arg(value.toDouble());
              QCheckBox* checkbox = new QCheckBox(text, ui->centralwidget);
              layout->addWidget(checkbox);
        }
    }





    // Set the model and hide the ID column:
    ui->singleSelectTable->setModel(property_model);
    ui->singleSelectTable->setColumnHidden(property_model->fieldIndex("id"), true);
    ui->singleSelectTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->singleSelectTable->setCurrentIndex(property_model->index(0, 0));



}

Dish::~Dish()
{
    delete ui;
}

void Dish::on_goBackButton_clicked()
{
    this->dish_list_window->setEnabled(true);
    this->close();
}


