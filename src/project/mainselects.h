#ifndef MAINSELECTS_H
#define MAINSELECTS_H

#include <QDialog>

namespace Ui {
class mainSelects;
}

class mainSelects : public QDialog
{
    Q_OBJECT

public:
    explicit mainSelects(QString position, int user_id, QWidget *parent = nullptr);
    ~mainSelects();

private:
    Ui::mainSelects *ui;
    QString position;
    int user_id;
};

#endif // MAINSELECTS_H
