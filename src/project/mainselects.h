#ifndef MAINSELECTS_H
#define MAINSELECTS_H

#include <QDialog>
#include <userprofile.h>

namespace Ui {
class mainSelects;
}

class mainSelects : public QDialog
{
    Q_OBJECT

public:
    explicit mainSelects(QString position, int user_id, QWidget *parent = nullptr);
    ~mainSelects();

private slots:
    void on_profileButton_clicked();

    void on_button_orders_clicked();

    void on_button_carriages_clicked();

    void on_button_stantions_pressed();

    void on_button_locomotives_pressed();

    void on_button_workers_pressed();

private:
    Ui::mainSelects *ui;
    userProfile *windowUserProfile;
    QString position;
    int user_id;
};

#endif // MAINSELECTS_H
