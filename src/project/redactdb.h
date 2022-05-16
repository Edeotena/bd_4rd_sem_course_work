#ifndef REDACTDB_H
#define REDACTDB_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>

namespace Ui {
class redactDB;
}

class redactDB : public QDialog
{
    Q_OBJECT

public:
    explicit redactDB(QString position, int user_id, QWidget *parent = nullptr);
    QStringList get_tables();
    ~redactDB();

private slots:
    void on_pushButton_2_pressed();

    void on_comboBox_textActivated(const QString &arg1);

private:
    Ui::redactDB *ui;
    QString position;
    int user_id;
    QSqlTableModel *table;

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

#endif // REDACTDB_H
