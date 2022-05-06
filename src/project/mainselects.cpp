#include "mainselects.h"
#include "ui_mainselects.h"

mainSelects::mainSelects(QString position, int user_id, QWidget *parent) :
    position(position),
    user_id(user_id),
    QDialog(parent),
    ui(new Ui::mainSelects)
{
    ui->setupUi(this);
    this->setWindowTitle("Choose select");
}

mainSelects::~mainSelects()
{
    delete ui;
}
