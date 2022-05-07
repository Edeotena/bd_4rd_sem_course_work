#include "userprofile.h"
#include "ui_userprofile.h"
#include <mainwindow.h>
#include <mainselects.h>
#include <QMessageBox>

userProfile::userProfile(QString position, int user_id, QWidget *parent) :
    position(position),
    user_id(user_id),
    QDialog(parent),
    ui(new Ui::userProfile)
{
    ui->setupUi(this);
    this->setWindowTitle("You'r profile");
    QSqlDatabase db = get_db();
    if (!db.open()) {
        QMessageBox::warning(this, "Ошибка!", "Не удалось открыть базу данных!");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT id_worker, login FROM qt_user WHERE id = '" + QString::number(user_id) + "'");
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса.";
        QMessageBox::warning(this, "Ошибка!", "Сервер не смог выполнить поиск!");
        db.close();
        return;
    }

    if (query.size() == 0) {
        qDebug() << "Пользователь не найден.";
        QMessageBox::warning(this, "Ошибка!", "Пользователя больше нет в БД!");
        db.close();
        return;
    }

    query.first();
    int worker_id = query.value(0).toInt();
    QString login = query.value(1).toString();
    query.prepare("SELECT full_name, salary FROM worker WHERE id = '" + QString::number(worker_id) + "'");
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса.";
        QMessageBox::warning(this, "Ошибка!", "Сервер не смог выполнить поиск!");
        db.close();
        return;
    }

    if (query.size() == 0) {
        qDebug() << "Пользователь не найден.";
        QMessageBox::warning(this, "Ошибка!", "Пользователя больше нет в БД!");
        db.close();
        return;
    }

    query.first();
    QString full_name = query.value(0).toString();
    int salary = query.value(1).toInt();

    ui->label_salary->setText(QString::number(salary));
    ui->label_id->setText(QString::number(worker_id));
    ui->label_position->setText(position);
    ui->label_name->setText(full_name);
    ui->label_login->setText(login);
    db.close();
}

userProfile::~userProfile()
{
    delete ui;
}

void userProfile::on_pushButton_2_clicked()
{
    MainWindow *newWindow = new MainWindow;
    newWindow->show();
    this->close();
}


void userProfile::on_pushButton_clicked()
{
    mainSelects *newWindow = new mainSelects(position, user_id);
    newWindow->show();
    this->close();
}

