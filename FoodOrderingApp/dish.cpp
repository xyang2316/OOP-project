#include "dish.h"
#include "ui_dish.h"
#include <string>
#include <QString>
#include <iostream>
#include <QCheckBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QButtonGroup>

Dish::Dish(QWidget *dish_list_window, int dish_id, double dish_price, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dish)
{
    this->dish_list_window = dish_list_window;
    ui->setupUi(this);
    this->dish_id = dish_id;
    dishSum = dish_price;

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

    // Generate checkboxes
    for (int row = 0; row < property_model->rowCount(); row++) {
        QByteArray tempjson = property_model->record(row).field("propertyJSON").value().toByteArray();
        QJsonObject json = QJsonDocument::fromJson(tempjson).object();
        QByteArray labelText = property_model->record(row).field("property").value().toByteArray();
//        QLabel* label = new QLabel(labelText);
//        layout->addWidget(label);
        QGroupBox *groupbox = new QGroupBox(tr(labelText));
        layout->addWidget(groupbox);
//        layout->setDirection(QVBoxLayout::TopToBottom);
        QVBoxLayout *vbox = new QVBoxLayout;
        foreach(const QString& key, json.keys()) {
              QJsonValue value = json.value(key);
              QString text = QString("%1 : $%2").arg(key).arg(value.toDouble(),5,'f',2);
              QRadioButton* radiobutton = new QRadioButton(text, ui->centralwidget);
//              vbox->setDirection(QVBoxLayout::TopToBottom);
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
//        QString labelText = property_model->record(row).field("property").value().toString();
//        QLabel* label = new QLabel(labelText);
//        layout->addWidget(label);
        QGroupBox *groupbox = new QGroupBox(tr(labelText));
        layout->addWidget(groupbox);
        QVBoxLayout *vbox = new QVBoxLayout;
//        QButtonGroup group;
        foreach(const QString& key, json.keys()) {
              QJsonValue value = json.value(key);
              QString text = QString("%1 : $%2").arg(key).arg(value.toDouble(),5,'f',2);
              QCheckBox* checkbox = new QCheckBox(text, ui->centralwidget);
//              group.addButton(checkbox);
              vbox->addWidget(checkbox);
        }
        groupbox->setLayout(vbox);
    }

//    // Set the model and hide the ID column:
//    ui->multiSelectTable->setModel(property_model);
//    ui->multiSelectTable->setColumnHidden(property_model->fieldIndex("id"), true);
//    ui->multiSelectTable->setSelectionMode(QAbstractItemView::MultiSelection);
//    ui->multiSelectTable->setCurrentIndex(property_model->index(0, 0));
////Display temp balance






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
    QList<QString> choices = {};
    if (allGroupboxes.size() > 0) {
        for(int i = 0; i < allGroupboxes.size(); ++i){
            QString title = allGroupboxes[i]->title();
            choices.push_back(title);
            QList<QRadioButton *> allButtons = allGroupboxes[i]->findChildren<QRadioButton *>();
//            qDebug() << allButtons;
            if (allButtons.isEmpty()) {
                QList<QCheckBox *> allButtons = allGroupboxes[i]->findChildren<QCheckBox *>();
                for(int i = 0; i < allButtons.size(); ++i){
                    if(allButtons.at(i)->isChecked()){
                         choices.push_back(allButtons.at(i)->text());
                    }
                }
            }

            for(int i = 0; i < allButtons.size(); ++i){
                if(allButtons.at(i)->isChecked()) {
                     choices.push_back(allButtons.at(i)->text());
                }
            }
        }
    }
    qDebug() << choices;
//    foreach (QString choice, choices) {
////        QString key = reg
//        QList list = choice.split(QLatin1String(" : $ "));
//        qDebug() << list;
//        memory[list[0]]= list[1].toDouble();
//    }
//    qDebug() << memory;
}

