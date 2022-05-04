#include "mainwindow.h"
#include <QMessageBox>
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QSqlDatabase get_db() {
    QSqlDatabase database = QSqlDatabase::addDatabase("QPSQL");
    database.setHostName("localhost");
    database.setPort(5432);
    database.setDatabaseName("db_curs");
    database.setUserName("postgres");
    database.setPassword("kudasmotrish");
    return database;
}


void MainWindow::on_pushButton_clicked()
{
    QString login = ui->login->text();
    QString pass = ui->pass->text();
    QSqlDatabase db = get_db();
    if (!db.open()) {
        QMessageBox::warning(this, "Ошибка!", "Не удалось открыть базу данных!");
    } else {
        QSqlQuery query;
        query.prepare("SELECT id from qt_user WHERE login = '" + login + "' AND password = '" + pass + "'");
        if (query.exec()) {
           if (query.size() > 0) {
              int id = query.value(0).toInt();
              qDebug() << id << " авторизовался.";
           } else {
                qDebug() << "Ошибка авторизации.";
                QMessageBox::warning(this, "Ошибка!", "Неправильный логин или пароль!");
                ui->login->clear();
                ui->login->clear();
           }
        } else {
            qDebug() << "Ошибка выполнения запроса.";
            QMessageBox::warning(this, "Ошибка!", "Сервер не смог выполнить поиск!");
            ui->login->clear();
            ui->login->clear();
        }
    }
    db.close();
}

