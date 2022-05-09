#include "selectworkers.h"
#include "ui_selectworkers.h"
#include "mainselects.h"
#include <QMessageBox>

selectWorkers::selectWorkers(QString position, int user_id, QWidget *parent) :
    position(position),
    user_id(user_id),
    QDialog(parent),
    ui(new Ui::selectWorkers)
{
    ui->setupUi(this);
    this->setWindowTitle("Select workers");
}


void selectWorkers::setTable(QString position, int size) {
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Код сотрудника" << "Имя" << "Должность" << "Зарплата" << "Данные паспорта" << "Дата назначения");
    ui->tableWidget->setRowCount(size);
}

QString selectWorkers::getValue(QString input) {
    bool ok = false;
    input.toInt(&ok);
    if (!ok && input != "") {
        return "bad input";
    }
    return input;
}

selectWorkers::~selectWorkers()
{
    delete ui;
}

void selectWorkers::on_pushButton_2_pressed()
{
    mainSelects *newWindow = new mainSelects(position, user_id);
    this->close();
    newWindow->show();
}


void selectWorkers::on_pushButton_3_pressed()
{
    QSqlDatabase db = get_db();
    QSqlQuery query;
    bool ok;
    QString worker_id = ui->lineEdit_8->text();
    worker_id.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка!", "ID сотрудника должно быть натуральным числом");
        ui->lineEdit_10->clear();
        ui->lineEdit_8->clear();
        ui->lineEdit_9->clear();
        ui->lineEdit_11->clear();
        return;
    }

    if(!db.open()) {
        QMessageBox::warning(this, "Ошибка!", "Не удалось открыть базу данных!");
        return;
    }

    QString update = "UPDATE qt_user SET access = 'yes' WHERE id_worker = " + worker_id;
    query.prepare(update);

    if (!query.exec()) {
        QMessageBox::warning(this, "Ошибка!", "Не удалось выполнить обновление!");
        db.close();
        return;
    }
    QMessageBox::information(this, "Успех!", "Пользователь обновлен!");
    db.close();
}


void selectWorkers::on_pushButton_pressed()
{
    QString id = getValue(ui->lineEdit_8->text());
    QString worker_position = ui->lineEdit_9->text();
    QString min_salary = getValue(ui->lineEdit_10->text());
    QString max_salary = getValue(ui->lineEdit_11->text());

    if (id == "bad input" || worker_position == "bad input" || min_salary == "bad input" || max_salary == "bad input") {
        QMessageBox::warning(this, "Ошибка!", "Вводимые поля(кроме должности) должны быть натуральными числами.");
        ui->lineEdit_8->clear();
        ui->lineEdit_9->clear();
        ui->lineEdit_10->clear();
        ui->lineEdit_11->clear();
        return;
    }
    QString select = "SELECT w.id, w.full_name, w.position, w.salary, w.passport, w.work_experience FROM worker w WHERE 1 = 1";
    if (id != "") {
        select += " AND w.id = " + id;
    }
    if (worker_position != "") {
        select += " AND w.position = '" + worker_position + "'";
    }
    if (min_salary != "") {
        select += " AND w.salary >= " + min_salary;
    }
    if (max_salary != "") {
        select += " AND w.salary <= " + max_salary;
    }
    select += " ORDER by w.id";
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


    ui->label_12->setText(QString::number(query.size()));
    setTable(position, query.size());

    int i = 0;
    while(query.next()) {
        for (int j = 0; j < 6; ++j) {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
        }
        ++i;
    }
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->resizeColumnsToContents();
    db.close();
}

