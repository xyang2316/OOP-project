#include "cart.h"
#include "ui_cart.h"

Cart::Cart(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Cart)
{
    ui->setupUi(this);
}

Cart::~Cart()
{
    delete ui;
}
