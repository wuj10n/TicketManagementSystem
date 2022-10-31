#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"manage.h"
#include"client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void changeClient();
    void changeManage();

private slots:
    void on_pushButtonLogin_clicked();
    void on_pushButtonExit_clicked();

private:
    Ui::MainWindow *ui;
    client *sw;
    manage *tw;
    order *od;
};

#endif // MAINWINDOW_H
