#include "selectorders.h"
#include "ui_selectorders.h"
#include "mainselects.h"
#include <QMessageBox>

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

void selectOrders::on_pushButton_2_clicked()
{
    mainSelects *newWindow = new mainSelects(position, user_id);
    this->close();
    newWindow->show();
}

void selectOrders::setTable(QString position, int size) {
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

QString getValue(QString input) {
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

void selectOrders::on_pushButton_clicked()
{

    if (position == "admin") {
        QString driver_id = getValue(ui->lineEdit->text());
        QString station_to = getValue(ui->lineEdit_2->text());
        QString station_from = getValue(ui->lineEdit_3->text());
        QString company = getValue(ui->lineEdit_7->text());

        if (driver_id == "bad input" || station_to == "bad input" || station_from == "bad input" || company == "bad input") {
            QMessageBox::warning(this, "Ошибка!", "Вводимые поля должны быть натуральными числами.");
            ui->lineEdit->clear();
            ui->lineEdit_2->clear();
            ui->lineEdit_3->clear();
            ui->lineEdit_7->clear();
            return;
        }
        QString select = "SELECT o.id, o.railway_carriage, w.full_name, s1.settlement, s2.settlement, o.price, o.cargo_name, o.cargo_weight, o.cargo_description, o.order_date, c.name FROM cargo_order o, worker w, station s1, station s2, customer_company c WHERE o.driver = w.id AND o.start_station = s1.id AND o.end_station = s2.id AND o.customer_company   = c.id";
        if (driver_id != "" || station_to != "" || station_from != "" || company != "") {
            select += " AND ";
        }
        if (driver_id != "") {
            select += "o.driver" + driver_id;
            if (station_to != "" || station_from != "" || company != "") {
                select += " AND ";
            }
        }
        if (station_to != "") {
            select += "o.start_station" + station_to;
            if (station_from != "" || company != "") {
                select += " AND ";
            }
        }
        if (station_from != "") {
            select += "o.end_station" + station_from;
            if (company != "") {
                select += " AND ";
            }
        }
        if (company != "") {
            select += "o.customer_company" + company;
        }
        select += " ORDER BY o.id";
        qDebug() << select;

        QSqlDatabase db = get_db();
        if (!db.open()) {
            QMessageBox::warning(this, "Ошибка!", "Не удалось открыть базу данных!");
            return;
        }

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
            for (int j = 0; j < 11; ++j) {
                ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
            }
            ++i;
        }
        ui->tableWidget->verticalHeader()->hide();
        ui->tableWidget->resizeColumnsToContents();
        db.close();
    } else if (position[0] == 'd') {
        QString station_to = getValue(ui->lineEdit_2->text());
        QString station_from = getValue(ui->lineEdit_3->text());

        QString select = "SELECT o.id, o.railway_carriage, w.full_name, s1.settlement, s2.settlement, o.cargo_name, o.cargo_weight, o.cargo_description FROM cargo_order o, worker w, station s1, station s2 WHERE o.driver = w.id AND o.start_station = s1.id AND o.end_station = s2.id AND o.driver = " + QString::number(user_id);
        if (station_to != "" || station_from != "") {
            select += " AND ";
        }
        if (station_to != "") {
            select += "o.start_station" + station_to;
            if (station_from != "") {
                select += " AND ";
            }
        }
        if (station_from != "") {
            select += "o.end_station" + station_from;
        }
        select += " ORDER BY o.id";
        qDebug() << select;
        QSqlDatabase db = get_db();
        if (!db.open()) {
            QMessageBox::warning(this, "Ошибка!", "Не удалось открыть базу данных!");
            return;
        }

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
            for (int j = 0; j < 8; ++j) {
                ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
            }
            ++i;
        }
        ui->tableWidget->verticalHeader()->hide();
        ui->tableWidget->resizeColumnsToContents();
        db.close();
    } else if (position[0] == 'l') {

        QString select = "SELECT DISTINCT  o.id, o.railway_carriage, o.cargo_name, o.cargo_weight, o.cargo_description FROM cargo_order o, loading_brigade l WHERE l.worker = " + QString::number(user_id) + " AND l.cargo_order = o.id ORDER BY o.id";

        qDebug() << select;
        QSqlDatabase db = get_db();
        if (!db.open()) {
            QMessageBox::warning(this, "Ошибка!", "Не удалось открыть базу данных!");
            return;
        }

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
            for (int j = 0; j < 5; ++j) {
                ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
            }
            ++i;
        }
        ui->tableWidget->verticalHeader()->hide();
        ui->tableWidget->resizeColumnsToContents();
        db.close();
    }
}

