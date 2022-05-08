#include "selectorders.h"
#include "ui_selectorders.h"

selectOrders::selectOrders(QString position, int user_id, QWidget *parent) :
    position(position),
    user_id(user_id),
    QDialog(parent),
    ui(new Ui::selectOrders)
{
    ui->setupUi(this);
    this->setWindowTitle("Select orders");
}

selectOrders::~selectOrders()
{
    delete ui;
}
