#ifndef SELECTLOCOMOTIVES_H
#define SELECTLOCOMOTIVES_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>

namespace Ui {
class selectLocomotives;
}

class selectLocomotives : public QDialog
{
    Q_OBJECT

public:
    explicit selectLocomotives(QString position, int user_id, QWidget *parent = nullptr);
    void setTable(QString position, int size);
    QString getValue(QString input);
    ~selectLocomotives();

private slots:
    void on_pushButton_2_pressed();

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
    Ui::selectLocomotives *ui;
    QString position;
    int user_id;
};

#endif // SELECTLOCOMOTIVES_H
