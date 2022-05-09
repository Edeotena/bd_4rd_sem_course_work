#ifndef SELECTWORKERS_H
#define SELECTWORKERS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>

namespace Ui {
class selectWorkers;
}

class selectWorkers : public QDialog
{
    Q_OBJECT

public:
    explicit selectWorkers(QString position, int user_id, QWidget *parent = nullptr);
    void setTable(QString position, int size);
    QString getValue(QString input);
    ~selectWorkers();

private slots:
    void on_pushButton_2_pressed();

    void on_pushButton_3_pressed();

    void on_pushButton_pressed();

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
    Ui::selectWorkers *ui;
    QString position;
    int user_id;

};

#endif // SELECTWORKERS_H
