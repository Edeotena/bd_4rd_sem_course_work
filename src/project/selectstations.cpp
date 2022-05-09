#include "selectstations.h"
#include "ui_selectstations.h"
#include "mainselects.h"
#include <QMessageBox>

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
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Код станции" << "Населенный поселок" << "Широта" << "Долгота" << "Имя машиниста" << "Код заказа" << "Название груза");
    ui->tableWidget->setRowCount(size);
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

void selectStations::on_pushButton_2_pressed()
{
    mainSelects *newWindow = new mainSelects(position, user_id);
    this->close();
    newWindow->show();
}


void selectStations::on_pushButton_pressed()
{
    QString driver_id = getValue(ui->lineEdit_5->text());
    QString station_to = getValue(ui->lineEdit_4->text());
    QString station_from = getValue(ui->lineEdit_6->text());

    if (driver_id == "bad input" || station_to == "bad input" || station_from == "bad input") {
        QMessageBox::warning(this, "Ошибка!", "Вводимые поля должны быть натуральными числами.");
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->lineEdit_6->clear();
        return;
    }

    QString select = "SELECT s.id, s.settlement, s.latitude, s.longitude, d.full_name, o.id, o.cargo_name FROM station s, cargo_order o, worker d WHERE (o.start_station = s.id OR o.end_station = s.id) AND o.driver = d.id";
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

    if (driver_id != "") {
        select += " AND d.id" + driver_id;
    }
    if (station_from != "") {
        select += " AND o.start_station" + station_from;
    }
    if (station_to != "") {
        select += " AND o.end_station" + station_to;
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

