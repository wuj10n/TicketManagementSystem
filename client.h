#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class client;
}

class client : public QWidget
{
    Q_OBJECT

public:
    explicit client(QWidget *parent = nullptr);
    ~client();
    void sendSignal();
    QSqlDatabase db;

signals:
    void mySignal();

private slots:
    void on_pushButtonReturn_clicked();

    void on_pushButtonBuy_clicked();

    void on_pushButtonAns_clicked();

    void on_pushButtonFresh_clicked();

private:
    Ui::client *ui;
    QSqlTableModel *model;
};

#endif // CLIENT_H

