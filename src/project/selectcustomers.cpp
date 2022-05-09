#include "selectcustomers.h"
#include "ui_selectcustomers.h"
#include "mainselects.h"
#include <QMessageBox>

selectCustomers::selectCustomers(QString position, int user_id, QWidget *parent) :
    position(position),
    user_id(user_id),
    QDialog(parent),
    ui(new Ui::selectCustomers)
{
    ui->setupUi(this);
    this->setWindowTitle("Select customers");
}

selectCustomers::~selectCustomers()
{
    delete ui;
}

void selectCustomers::setTable(QString position, int size) {
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Код компании" << "Название компании" << "Телефон" << "Почта" << "Код заказа" << "Название груза");
    ui->tableWidget->setRowCount(size);
}

QString selectCustomers::getValue(QString input) {
    bool ok = false;
    input.toInt(&ok);
    if (!ok && input != "") {
        return "bad input";
    }
    return input;
}

void selectCustomers::on_pushButton_2_pressed()
{
    mainSelects *newWindow = new mainSelects(position, user_id);
    this->close();
    newWindow->show();
}


void selectCustomers::on_pushButton_pressed()
{
    QString id = getValue(ui->lineEdit_8->text());
    QString company_name = ui->lineEdit_9->text();
    QString order_id = getValue(ui->lineEdit_10->text());

    if (id == "bad input" || company_name == "bad input" || order_id == "bad input") {
        QMessageBox::warning(this, "Ошибка!", "Вводимые поля(кроме должности) должны быть натуральными числами.");
        ui->lineEdit_8->clear();
        ui->lineEdit_9->clear();
        ui->lineEdit_10->clear();
        return;
    }
    QString select = "SELECT c.id, c.name, c.contact_number, c.contact_mail, o.id, o.cargo_name FROM customer_company c, cargo_order o WHERE o.customer_company = c.id";
    if (id != "") {
        select += " AND c.id = " + id;
    }
    if (company_name != "") {
        select += " AND c.name = '" + company_name + "'";
    }
    if (order_id != "") {
        select += " AND o.id = " + order_id;
    }
    select += " ORDER by c.id";
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

