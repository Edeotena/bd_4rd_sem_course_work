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
    QSqlDatabase db = get_db();
    db.open();
    table = new QSqlTableModel(this, db);
    table->setTable("cargo_order");
    table->select();
    ui->tableView->setModel(table);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
    ui->tableView->setShowGrid(false);
    db.close();
}

