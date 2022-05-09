#include "mainselects.h"
#include "ui_mainselects.h"
#include "selectorders.h"
#include "selectcarriages.h"
#include "selectstations.h"
#include "selectlocomotives.h"
#include <QMessageBox>

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

void mainSelects::on_profileButton_clicked()
{
    windowUserProfile = new userProfile(position, user_id);
    this->close();
    windowUserProfile->show();
}


void mainSelects::on_button_orders_clicked()
{
    selectOrders *windowSelectOrders = new selectOrders(position, user_id);
    this->close();
    windowSelectOrders->show();
}


void mainSelects::on_button_carriages_clicked()
{
    selectCarriages *windowSelectCarriages = new selectCarriages(position, user_id);
    this->close();
    windowSelectCarriages->show();
}


void mainSelects::on_button_stantions_pressed()
{
    if (position[0] == 'l') {
        QMessageBox::warning(this, "Ошибка!", "У Вас нет доступа к поискам такого типа!");
        return;
    }
    selectStations *windowSelectStations = new selectStations(position, user_id);
    this->close();
    windowSelectStations->show();
}


void mainSelects::on_button_locomotives_pressed()
{
    if (position[0] == 'l') {
        QMessageBox::warning(this, "Ошибка!", "У Вас нет доступа к поискам такого типа!");
        return;
    }
    selectLocomotives *windowSelectLocomotives = new selectLocomotives(position, user_id);
    this->close();
    windowSelectLocomotives->show();
}

