#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <userprofile.h>

namespace Ui {
class userProfile;
}

class userProfile : public QDialog
{
    Q_OBJECT

public:
    explicit userProfile(QString position, int user_id, QWidget *parent = nullptr);
    ~userProfile();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::userProfile *ui;
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

#endif // USERPROFILE_H
