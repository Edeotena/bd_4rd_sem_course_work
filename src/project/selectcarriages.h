#ifndef SELECTCARRIAGES_H
#define SELECTCARRIAGES_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>

namespace Ui {
class selectCarriages;
}

class selectCarriages : public QDialog
{
    Q_OBJECT

public:
    explicit selectCarriages(QString position, int user_id, QWidget *parent = nullptr);
    void setTable(QString position, int size);
    QString getValue(QString input);
    ~selectCarriages();

private slots:
    void on_pushButton_2_pressed();

    void on_pushButton_pressed();

private:
    Ui::selectCarriages *ui;
    QString position;
    int user_id;

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
};

#endif // SELECTCARRIAGES_H
