#ifndef MANAGE_H
#define MANAGE_H

#include <QWidget>
#include<QSqlTableModel>
#include<order.h>

namespace Ui {
class manage;
}

class manage : public QWidget
{
    Q_OBJECT

public:
    explicit manage(QWidget *parent = nullptr);
    ~manage();
    QSqlDatabase db;
    void refresh();
    void sendSignal();
    void changeOrder();

signals:
    void mySignal();

private slots:
    void on_pushButtonReturn_clicked();

    void on_pushButtonFlightid_clicked();

    void on_pushButtonStart_clicked();

    void on_pushButtonCancel_clicked();

    void on_pushButtonSure_clicked();

    void on_pushButtonDelete_clicked();

    void on_pushButtonAdd_clicked();

    void on_pushButtonFresh_clicked();

    void on_pushButtonOrder_clicked();


private:
    Ui::manage *ui;
    QSqlTableModel *model;
    order *od;
};

#endif // MANAGE_H
