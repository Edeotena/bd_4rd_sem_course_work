#ifndef SELECTORDERS_H
#define SELECTORDERS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>

namespace Ui {
class selectOrders;
}

class selectOrders : public QDialog
{
    Q_OBJECT

public:
    explicit selectOrders(QString position, int user_id, QWidget *parent = nullptr);
    void setTable(QString position, int size);
    ~selectOrders();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    QSqlDatabase get_db() {
        QSqlDatabase database = QSqlDatabase::addDatabase("QPSQL");
        database.setHostName("localhost");
        database.setPort(5432);
        database.setDatabaseName("db_curs");
        database.setUserName("postgres");
        database.setPassword("kudasmotrish");
        return database;
    }

private:
    Ui::selectOrders *ui;
    QString position;
    int user_id;
};

#endif // SELECTORDERS_H
