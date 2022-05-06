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

private:
    Ui::mainSelects *ui;
    userProfile *windowUserProfile;
    QString position;
    int user_id;
};

#endif // MAINSELECTS_H
