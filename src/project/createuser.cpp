#include "createuser.h"
#include "ui_createuser.h"
#include <QMessageBox>
#include "mainwindow.h"

createUser::createUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createUser)
{
    ui->setupUi(this);
    this->setWindowTitle("Registration");
}

createUser::~createUser()
{
    delete ui;
}

void createUser::on_pushButton_clicked()
{
    QString login = ui->login->text();
    QString pass = ui->pass->text();
    QString id = ui->id->text();
    ui->login->clear();
    ui->pass->clear();
    ui->id->clear();

    bool ok_id;
    id.toInt(&ok_id);
    if (login == "" || pass == "" || id == "" || !ok_id) {
        QMessageBox::warning(this, "Ошибка!", "Пароль, логин и id не должны быть пустыми!\n id должен быть натуральным числом!");
        return;
    }

    QSqlDatabase db = createUser::get_db();
    if (!db.open()) {
        QMessageBox::warning(this, "Ошибка!", "Не удалось открыть базу данных!");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT MAX(id) FROM qt_user");
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса.";
        QMessageBox::warning(this, "Ошибка!", "Сервер не смог выполнить поиск!");
        db.close();
        return;
    }

    int max = 1;
    if (query.size() > 0) {
        query.first();
        max = query.value(0).toInt() + 1;
    }

    query.prepare("INSERT INTO qt_user (id, id_worker, access, login, password) VALUES (" + QString::number(max) + ", " + id + ", 'no', '" + login + "', '" + pass + "')");
    if (!query.exec()) {
        qDebug() << "Ошибка добавления записи.";
        QMessageBox::warning(this, "Ошибка!", "Выберите другой логин!");
        db.close();
        return;
    }

    qDebug() << "Запись добавлена.";
    QMessageBox::information(this, "Успех!", "Пользователь создан!");
    this->close();
    db.close();
    emit loginWindow();
}

void createUser::on_pushButton_2_clicked()
{
    this->close();
    emit loginWindow();
}

