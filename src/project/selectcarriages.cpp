#include "selectcarriages.h"
#include <QMessageBox>
#include "ui_selectcarriages.h"
#include "mainselects.h"

selectCarriages::selectCarriages(QString position, int user_id, QWidget *parent) :
    position(position),
    user_id(user_id),
    QDialog(parent),
    ui(new Ui::selectCarriages)
{
    ui->setupUi(this);
    this->setWindowTitle("Select railway carriage");
}

selectCarriages::~selectCarriages()
{
    delete ui;
}

void selectCarriages::setTable(QString position, int size) {
    if (position == "admin") {
        ui->tableWidget->setColumnCount(6);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Код вагона" << "Код поезда" << "Модель вагона" << "Дата тех.обслуживания" << "Название груза" << "Вес груза");
        ui->tableWidget->setRowCount(size);
    } else if (position[0] == 'd') {
        ui->tableWidget->setColumnCount(5);
        ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Код вагона" << "Код поезда" << "Модель вагона" << "Название груза" << "Вес груза");
        ui->tableWidget->setRowCount(size);
    } else if (position[0] == 'l') {
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Код вагона" << "Модель вагона" << "Название груза" << "Вес груза");
    ui->tableWidget->setRowCount(size);
    }
}

QString selectCarriages::getValue(QString input) {
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

void selectCarriages::on_pushButton_2_pressed()
{
    mainSelects *newWindow = new mainSelects(position, user_id);
    this->close();
    newWindow->show();
}


void selectCarriages::on_pushButton_pressed()
{
    QString id_carriage = getValue(ui->lineEdit->text());
    QString id_locomotive = getValue(ui->lineEdit_2->text());
    QString id_order = getValue(ui->lineEdit_3->text());
    QString select;
    int size;

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

    if (id_carriage == "bad input" || id_locomotive == "bad input" || id_order == "bad input") {
        QMessageBox::warning(this, "Ошибка!", "Вводимые поля должны быть натуральными числами.");
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        return;
    }

    if (position == "admin") {
        select = "SELECT DISTINCT c.id, l.id, c.type, c.maintenance_date, o.cargo_name, o.cargo_weight FROM cargo_order o, locomotive l, railway_carriage c, composition_of_carriages cc  WHERE c.id = cc.railway_carriage AND cc.locomotive = l.id AND o.railway_carriage = c.id";
        if (id_carriage != "" || id_locomotive != "" || id_order != "") {
            select += " AND ";
        }
        if (id_carriage != "") {
            select += "c.id" + id_carriage;
            if (id_locomotive != "" || id_order != "") {
                select += " AND ";
            }
        }
        if (id_locomotive != "") {
            select += "cc.locomotive" + id_locomotive;
            if (id_order != "") {
                select += " AND ";
            }
        }
        if (id_order != "") {
            select += "o.id" + id_order;
        }
        select += " ORDER BY c.id";
        size = 6;

    } else if (position[0] == 'd') {
        select = "SELECT DISTINCT c.id, l.id, c.type, o.cargo_name, o.cargo_weight FROM cargo_order o, locomotive l, railway_carriage c, composition_of_carriages cc  WHERE c.id = cc.railway_carriage AND cc.locomotive = l.id AND o.railway_carriage = c.id AND o.driver = " + QString::number(worker_id);
        if (id_carriage != "" || id_locomotive != "" || id_order != "") {
            select += " AND ";
        }
        if (id_carriage != "") {
            select += "c.id" + id_carriage;
            if (id_locomotive != "" || id_order != "") {
                select += " AND ";
            }
        }
        if (id_locomotive != "") {
            select += "cc.locomotive" + id_locomotive;
            if (id_order != "") {
                select += " AND ";
            }
        }
        if (id_order != "") {
            select += "o.id" + id_order;
        }
        select += " ORDER BY c.id";
        size = 5;

    } else if (position[0] == 'l') {
        select = "SELECT DISTINCT c.id, c.type, o.cargo_name, o.cargo_weight FROM cargo_order o, locomotive l, railway_carriage c, composition_of_carriages cc, loading_brigade lb WHERE c.id = cc.railway_carriage AND cc.locomotive = l.id AND o.railway_carriage = c.id AND lb.worker = " + QString::number(worker_id) + " AND lb.cargo_order = o.id";
        if (id_carriage != "" || id_locomotive != "" || id_order != "") {
            select += " AND ";
        }
        if (id_carriage != "") {
            select += "c.id" + id_carriage;
            if (id_locomotive != "" || id_order != "") {
                select += " AND ";
            }
        }
        if (id_locomotive != "") {
            select += "cc.locomotive" + id_locomotive;
            if (id_order != "") {
                select += " AND ";
            }
        }
        if (id_order != "") {
            select += "o.id" + id_order;
        }
        select += " ORDER BY c.id";
        size = 4;
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


    ui->label_7->setText(QString::number(query.size()));
    setTable(position, query.size());

    int i = 0;
    while(query.next()) {
        for (int j = 0; j < size; ++j) {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
        }
        ++i;
    }
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->resizeColumnsToContents();
    db.close();
}

