#include "selectstations.h"
#include "ui_selectstations.h"

selectStations::selectStations(QString position, int user_id, QWidget *parent) :
    position(position),
    user_id(user_id),
    QDialog(parent),
    ui(new Ui::selectStations)
{
    ui->setupUi(this);
}

selectStations::~selectStations()
{
    delete ui;
}

void selectStations::setTable(QString position, int size) {
    if (position == "admin") {
        ui->tableWidget->setColumnCount(11);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Код заказа" << "Код вагона" << "Имя водителя" << "Пункт отправления" << "Пункт назначения" << "Стоимость" << "Название груза" << "Вес груза" << "Описание груза" << "Дата заказа" << "Компания-заказчик");
        ui->tableWidget->setRowCount(size);
    } else if (position[0] == 'd') {
        ui->tableWidget->setColumnCount(8);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Код заказа" << "Код вагона" << "Имя водителя" << "Пункт отправления" << "Пункт назначения" << "Название груза" << "Вес груза" << "Описание груза");
        ui->tableWidget->setRowCount(size);
    } else if (position[0] == 'l') {
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Код заказа" << "Код вагона" << "Название груза" << "Вес груза" << "Описание груза");
    ui->tableWidget->setRowCount(size);
    }
}

QString selectStations::getValue(QString input) {
    QString temp= "";
    bool ok = false;
    input.toInt(&ok);
    if (!ok && input != "") {
        return "bad input";
    }
    if (input != "") {
        temp = " = " + input;
    }
    return temp;
}
