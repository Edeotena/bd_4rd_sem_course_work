#include "otchets.h"
#include "ui_otchets.h"
#include "QMessageBox"
#include "mainselects.h"

otchets::otchets(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::otchets)
{
    ui->setupUi(this);
}

otchets::~otchets()
{
    delete ui;
}

void otchets::on_pushButton_3_pressed()
{
    mainSelects *newWindow = new mainSelects(position, user_id);
    this->close();
    newWindow->show();
}


void otchets::on_pushButton_pressed()
{
    QSqlDatabase db = get_db();
    QString select = "SELECT DISTINCT w.salary, (SELECT COUNT(wDet.salary)FROM worker AS wDet WHERE w.salary = wDet.salary) AS count FROM worker AS w";
    QSqlQuery query;
    db.open();
    query.prepare(select);
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса.";
        QMessageBox::warning(this, "Ошибка!", "Сервер не смог выполнить поиск!");
        db.close();
        return;
    }
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Зарплата" << "Количество");
    ui->tableWidget->setRowCount(query.size());

    int i = 0;
    while(query.next()) {
        for (int j = 0; j < 2; ++j) {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
        }
        ++i;
    }
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->resizeColumnsToContents();
    db.close();
}


void otchets::on_pushButton_2_pressed()
{
    QSqlDatabase db = get_db();
    QString select = "SELECT DISTINCT w.position, (SELECT MAX(wDet.salary) FROM worker AS wDet WHERE w.position = wDet.position) AS MaxSalary FROM worker AS w";
    QSqlQuery query;
    db.open();
    query.prepare(select);
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса.";
        QMessageBox::warning(this, "Ошибка!", "Сервер не смог выполнить поиск!");
        db.close();
        return;
    }
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Должность" << "Зарплата");
    ui->tableWidget->setRowCount(query.size());

    int i = 0;
    while(query.next()) {
        for (int j = 0; j < 2; ++j) {
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(query.value(j).toString()));
        }
        ++i;
    }
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->resizeColumnsToContents();
    db.close();
}

