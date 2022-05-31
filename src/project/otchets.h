#ifndef OTCHETS_H
#define OTCHETS_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>

namespace Ui {
class otchets;
}

class otchets : public QDialog
{
    Q_OBJECT

public:
    explicit otchets(QWidget *parent = nullptr);
    ~otchets();

private slots:
    void on_pushButton_3_pressed();

    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

private:
    Ui::otchets *ui;
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

#endif // OTCHETS_H
