#include "dish.h"
#include "ui_dish.h"
#include "cart.h"
#include "cartdata.h"
#include "global.h"
#include <string>
#include <QString>
#include <iostream>
#include <QCheckBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QButtonGroup>

Dish::Dish(QMap<QString, QWidget*> pointerStack, int dish_id, double dish_price, int restaurant_id, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dish)
{
//    dish_list_window_global = dish_list_window;//

//    this->dish_list_window = dish_list_window;
    this->pointerStack = pointerStack;
    this->dish_list_window = pointerStack["Menu"];
    this->restaurant_id = restaurant_id;
    ui->setupUi(this);
    this->dish_id = dish_id;
    dishSum = dish_price;

//    qDebug() << QString::number(dish_id);
//    property_model = new QSqlQueryModel(this);
//    property_model->setQuery("Select * from properties where book =" + QString::number(dish_id));
//    qDebug() << QString::number(dish_id);
//    ui->tableViewTest->setModel(property_model);

//     Create the data model:
//    property_model = new QSqlRelationalTableModel();
////    property_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
//    property_model->setTable("properties");

//    property_model->setRelation(property_model->fieldIndex("book"), QSqlRelation("Dish", "book", "property"));
//    if (!property_model->select()){
//        qDebug() << property_model->lastError();
//    };
//    ui->tableViewTest->setModel(property_model);

    property_model = new QSqlRelationalTableModel();
    // property_model = new QSqlRelationalTableModel(ui->singleSelectTable);
    property_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    property_model->setTable("properties");
    qDebug()<< "fieldindex"<<property_model->fieldIndex("book");
    // Set the relations to the other database tables:
    property_model->setRelation(property_model->fieldIndex("book"), QSqlRelation("Dish", "dish_id", "dish_name"));
    property_model->setHeaderData(property_model->fieldIndex("book"), Qt::Horizontal, tr("Dish"));
    property_model->setHeaderData(property_model->fieldIndex("property"), Qt::Horizontal, tr("Category"));
    property_model->setHeaderData(property_model->fieldIndex("propertyJSON"), Qt::Horizontal, tr("JSON"));
    if (!property_model->select()) {
        qDebug() << property_model->lastError();
    }

//// option box
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>( ui->verticalLayout->layout());
    layout->addStretch();
    layout->setDirection(QVBoxLayout::TopToBottom);
    // Populate the model:
    QString query = QString("book = %1 AND propertyType = 'single select'").arg(dish_id);
    property_model->setFilter(query);
    if (!property_model->select()) {
        return;
    }
//// single select
//    // Set the model and hide the ID column:
//    ui->singleSelectTable->setModel(property_model);
//    ui->singleSelectTable->setColumnHidden(property_model->fieldIndex("id"), true);
//    ui->singleSelectTable->setSelectionMode(QAbstractItemView::SingleSelection);
//    ui->singleSelectTable->setCurrentIndex(property_model->index(0, 0));

    // Generate radiobuttons
    for (int row = 0; row < property_model->rowCount(); row++) {
        QByteArray tempjson = property_model->record(row).field("propertyJSON").value().toByteArray();
        QJsonObject json = QJsonDocument::fromJson(tempjson).object();
        QByteArray labelText = property_model->record(row).field("property").value().toByteArray();
//        QLabel* label = new QLabel(labelText);
//        layout->addWidget(label);
        QGroupBox *groupbox = new QGroupBox(tr(labelText));
        layout->addWidget(groupbox);
        QVBoxLayout *vbox = new QVBoxLayout;
        foreach(const QString& key, json.keys()) {
              QJsonValue value = json.value(key);
              QString text = QString("%1 : $%2").arg(key).arg(value.toDouble(),5,'f',2);
              QRadioButton* radiobutton = new QRadioButton(text, ui->centralwidget);
              vbox->addWidget(radiobutton);
              if (key == json.keys()[0])
                  radiobutton->setChecked(true);
        }
        groupbox->setLayout(vbox);
    }


//// multiselect
    // Populate the model:
    QString query1 = QString("book = %1 AND propertyType = 'multi-select'").arg(dish_id);
    property_model->setFilter(query1);
    if (!property_model->select()) {
        return;
    }

    // Generate checkboxes
    for (int row = 0; row < property_model->rowCount(); row++) {
        QByteArray tempjson = property_model->record(row).field("propertyJSON").value().toByteArray();
        QJsonObject json = QJsonDocument::fromJson(tempjson).object();
        QByteArray labelText = property_model->record(row).field("property").value().toByteArray();
        QGroupBox *groupbox = new QGroupBox(tr(labelText));
        layout->addWidget(groupbox);
        QVBoxLayout *vbox = new QVBoxLayout;
        foreach(const QString& key, json.keys()) {
              QJsonValue value = json.value(key);
              QString text = QString("%1 : $%2").arg(key).arg(value.toDouble(),5,'f',2);
              QCheckBox* checkbox = new QCheckBox(text, ui->centralwidget);
              vbox->addWidget(checkbox);
        }
        groupbox->setLayout(vbox);
    }

////Display dynamic balance


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


void Dish::on_confirmButton_clicked()
{
    QList<QGroupBox *> allGroupboxes = ui->verticalLayout->parentWidget()->findChildren<QGroupBox *>();
    QList<QPair<QString, double>> choices = {};
    if (allGroupboxes.size() > 0) {
        for(int i = 0; i < allGroupboxes.size(); ++i){
            QString title = allGroupboxes[i]->title();
            QList<QRadioButton *> allButtons = allGroupboxes[i]->findChildren<QRadioButton *>();
//            qDebug() << allButtons;
            if (allButtons.isEmpty()) {
                QList<QCheckBox *> allButtons = allGroupboxes[i]->findChildren<QCheckBox *>();
                for(int i = 0; i < allButtons.size(); ++i){
                    if(allButtons.at(i)->isChecked()){
                        QList tempProp = allButtons.at(i)->text().split(QLatin1String(" : $ "));
                        QString tempStr = title + " : " + tempProp [0];
                        choices.push_back(QPair<QString, double>(tempStr, tempProp[1].toDouble()));
                    }
                }
            }

            for(int i = 0; i < allButtons.size(); ++i){
                if(allButtons.at(i)->isChecked()) {
                    QList tempProp = allButtons.at(i)->text().split(QLatin1String(" : $ "));
                    choices.push_back(QPair<QString, double>(title.append(" : ").append(tempProp[0]), tempProp[1].toDouble()));
                }
            }
        }
    }
    CartData::GetInstance()->addProperties(choices);
    qDebug() << CartData::GetInstance()->getPriceList();
    qDebug() << CartData::GetInstance()->getCart();

//    cart_window = new Cart(this, restaurant_id);
    pointerStack["Dish"] = this;
    cart_window = new Cart(pointerStack, restaurant_id);

    cart_window->show();
    this->dish_list_window->setEnabled(true);
    this->close();
}

