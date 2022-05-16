#include "redactdb.h"
#include "ui_redactdb.h"
#include "mainselects.h"
#include "mainwindow.h"
#include <QMessageBox>

QStringList redactDB::get_tables() {
    QSqlDatabase db =get_db();
    if (!db.open()) {
        QMessageBox::warning(this, "Ошибка!", "Не удалось открыть базу данных!");
    }
    QSqlQuery query;
    query.exec(QString("SELECT table_name FROM information_schema.tables WHERE table_schema='public' AND table_type='BASE TABLE'"));

    QStringList result;
    result.push_back("");
    while (query.next()) {
        result.push_back(query.value(0).toString());
        qDebug() << query.value(0).toString();
    }
    db.close();
    return result;
}

redactDB::redactDB(QString position, int user_id, QWidget *parent) :
    position(position),
    user_id(user_id),
    QDialog(parent),
    ui(new Ui::redactDB)
{
    ui->setupUi(this);
    QStringList tables = get_tables();
    ui->comboBox->addItems(tables);
    QSqlDatabase db = get_db();
    table = new QSqlTableModel(this, db);
}

redactDB::~redactDB()
{
    delete ui;
}

void redactDB::on_pushButton_2_pressed()
{
    mainSelects *newWindow = new mainSelects(position, user_id);
    this->close();
    newWindow->show();
}

void redactDB::on_comboBox_textActivated(const QString &arg1)
{
    QString table_name = ui->comboBox->currentText();
    QSqlDatabase db = get_db();
    if (!db.open()) {
        QMessageBox::warning(this, "Ошибка!", "Не удалось открыть базу данных!");
        return;
    }
    QSqlTableModel* model = new QSqlTableModel(ui->comboBox, db);
    model->setTable(table_name);
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->verticalHeader()->hide();
}

