#include "mainwindow.h"
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

QSqlDatabase set_database() {
    QSqlDatabase database = QSqlDatabase::addDatabase("QPSQL");
    database.setHostName("localhost");
    database.setPort(5432);
    database.setDatabaseName("db");
    database.setUserName("postgres");
    database.setPassword("?");
    return database;
}


void MainWindow::on_pushButton_clicked()
{
    QSqlDatabase db = set_database();
        if (db.open()) {
            ui->textBrowser->append("DB successfully opened!\n");
            for (const auto& i : db.tables()) {
                ui->textBrowser->append(i);
            }
        } else {
            ui->textBrowser->append("все плохо");
        }

        table = new QSqlTableModel(this, db);
        table->setTable("territory_data");
        table->select();
        ui->tableView->setModel(table);
        ui->tableView->resizeColumnsToContents();
        ui->tableView->resizeRowsToContents();
        //ui->tableView->resize(QSize(ui->tableView->horizontalHeader()->geometry()))

        db.close();
        ui->textBrowser->append("\nDB successfully closed!");

}

