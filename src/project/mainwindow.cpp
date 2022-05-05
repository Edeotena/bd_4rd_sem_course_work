#include "mainwindow.h"
#include <QMessageBox>
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    windowUserCreate = new createUser;
    connect(windowUserCreate, &createUser::loginWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString login = ui->login->text();
    QString pass = ui->pass->text();
    QSqlDatabase db = MainWindow::get_db();
    ui->login->clear();
    ui->pass->clear();
    if (!db.open()) {
        QMessageBox::warning(this, "Ошибка!", "Не удалось открыть базу данных!");
    } else {
        QSqlQuery query;
        query.prepare("SELECT id, access FROM qt_user WHERE login = '" + login + "' AND password = '" + pass + "'");
        if (query.exec()) {
           if (query.size() > 0) {
              query.first();
              if (query.value(1).toString() == "yes") {
                  int id = query.value(0).toInt();
                  qDebug() << id << " авторизовался.";
              } else {
                  qDebug() << "Пользователь еще не принят.";
                  QMessageBox::warning(this, "Ошибка!", "Вы еще не получили доступ к системе!");
              }
           } else {
                qDebug() << "Пользователь не найден.";
                QMessageBox::warning(this, "Ошибка!", "Неправильный логин или пароль!");
           }
        } else {
            qDebug() << "Ошибка выполнения запроса.";
            QMessageBox::warning(this, "Ошибка!", "Сервер не смог выполнить поиск!");
        }
    }
    db.close();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->login->clear();
    ui->pass->clear();
    windowUserCreate->show();
    this->close();
}

