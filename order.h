#ifndef ORDER_H
#define ORDER_H

#include <QWidget>
#include <QSqlTableModel>
#include <order.h>

namespace Ui {
class order;
}

class order : public QWidget
{
    Q_OBJECT

public:
    explicit order(QWidget *parent = nullptr);
    ~order();
    QSqlDatabase db;

private slots:
    void on_pushButtonFresh_clicked();

    void on_pushButtonSure_clicked();

    void on_pushButtonAdd_clicked();

    void on_pushButtonDelete_clicked();

private:
    Ui::order *ui;
    QSqlTableModel *model;
    order *od;
};

#endif // ORDER_H


