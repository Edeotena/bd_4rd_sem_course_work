#include "selectlocomotives.h"
#include "ui_selectlocomotives.h"
#include <QMessageBox>
#include "mainselects.h"

selectLocomotives::selectLocomotives(QString position, int user_id, QWidget *parent) :
    position(position),
    user_id(user_id),
    QDialog(parent),
    ui(new Ui::selectLocomotives)
{
    ui->setupUi(this);
    this->setWindowTitle("Select locomotives");
}

selectLocomotives::~selectLocomotives()
{
    delete ui;
}

void selectLocomotives::on_pushButton_2_pressed()
{
    mainSelects *newWindow = new mainSelects(position, user_id);
    this->close();
    newWindow->show();
}

void selectLocomotives::setTable(QString position, int size) {
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Код поезда" << "Модель поезда" << "Дата тех. обслуживания" << "Имя водителя" << "Код вагона" << "Код заказа" << "Название груза");
    ui->tableWidget->setRowCount(size);
}

QString selectLocomotives::getValue(QString input) {
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

void selectLocomotives::on_pushButton_pressed()
{
    QString locomotive_id = getValue(ui->lineEdit_5->text());
    QString driver_id = getValue(ui->lineEdit_6->text());
    QString order_id = getValue(ui->lineEdit_4->text());
    QString carriage_id = getValue(ui->lineEdit_7->text());

    if (driver_id == "bad input" || locomotive_id == "bad input" || order_id == "bad input" || carriage_id == "bad input") {
        QMessageBox::warning(this, "Ошибка!", "Вводимые поля должны быть натуральными числами.");
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        ui->lineEdit_7->clear();
        return;
    }

    QString select = "SELECT l.id, l.type, l.maintenance_date, d.full_name, c.id, o.id, o.cargo_name FROM cargo_order o, locomotive l, railway_carriage c, worker d, composition_of_carriages cc WHERE cc.railway_carriage = c.id AND cc.locomotive = l.id AND o.railway_carriage = c.id AND d.id = o.driver";
        if (position[0] == 'd') {
        QSqlDatabase db1 = get_db();
        if (!db1.open()) {
            QMessageBox::warning(this, "Ошибка!", "Не удалось открыть базу данных!");
            return;
        }

        QSqlQuery query1;
        query1.prepare("SELECT id_worker FROM qt_user WHERE id = '" + QString::number(user_id) + "'");
        if (!query1.exec()) {
            qDebug() << "Ошибка выполнения запроса.";
            QMessageBox::warning(this, "Ошибка!", "Сервер не смог выполнить поиск!");
            db1.close();
            return;
        }

        if (query1.size() == 0) {
            qDebug() << "Пользователь не найден.";
            QMessageBox::warning(this, "Ошибка!", "Пользователя больше нет в БД!");
            db1.close();
            return;
        }

        query1.first();
        int worker_id = query1.value(0).toInt();
        db1.close();
        select += " AND d.id = " + QString::number(worker_id);
    }

    if (locomotive_id != "") {
        select += " AND l.id" + locomotive_id;
    }
    if (driver_id != "") {
        select += " AND d.id" + driver_id;
    }
    if (order_id != "") {
        select += " AND o.id" + order_id;
    }
    if (carriage_id != "") {
        select += " AND c.id" + carriage_id;
    }

    QSqlDatabase db = get_db();
    if (!db.open()) {
        QMessageBox::warning(this, "Ошибка!", "Не удалось открыть базу данных!");
        return;
    }
    qDebug() << select;
    QSqlQuery query;
    query.prepare(select);
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса.";
        QMessageBox::warning(this, "Ошибка!", "Сервер не смог выполнить поиск!");
        db.close();
        return;
    }


    ui->label_9->setText(QString::number(query.size()));
    setTable(position, query.size());

    int i = 0;
    while(query.next()) {
        for (int j = 0; j < 7; ++j) {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
        }
        ++i;
    }
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->resizeColumnsToContents();
    db.close();
}

