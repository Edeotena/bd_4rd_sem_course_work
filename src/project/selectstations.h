#ifndef SELECTSTATIONS_H
#define SELECTSTATIONS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>


namespace Ui {
class selectStations;
}

class selectStations : public QDialog
{
    Q_OBJECT

public:
    explicit selectStations(QString position, int user_id, QWidget *parent = nullptr);
    void setTable(QString position, int size);
    QString getValue(QString input);
    ~selectStations();

private:
    Ui::selectStations *ui;
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



#endif // SELECTSTATIONS_H
