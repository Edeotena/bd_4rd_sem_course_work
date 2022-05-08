#include "selectcarriages.h"
#include "ui_selectcarriages.h"

selectCarriages::selectCarriages(QString position, int user_id, QWidget *parent) :
    position(position),
    user_id(user_id),
    QDialog(parent),
    ui(new Ui::selectCarriages)
{
    ui->setupUi(this);
}

selectCarriages::~selectCarriages()
{
    delete ui;
}
