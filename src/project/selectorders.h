#ifndef SELECTORDERS_H
#define SELECTORDERS_H

#include <QDialog>

namespace Ui {
class selectOrders;
}

class selectOrders : public QDialog
{
    Q_OBJECT

public:
    explicit selectOrders(QString position, int user_id, QWidget *parent = nullptr);
    ~selectOrders();

private:
    Ui::selectOrders *ui;
    QString position;
    int user_id;
};

#endif // SELECTORDERS_H
