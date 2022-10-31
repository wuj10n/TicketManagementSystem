#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "globle.h"
#include "client.h"
#include "manage.h"
#include <QString>
#include <QRadioButton>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint);
    setWindowTitle(QStringLiteral("民航登录系统"));
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
    ui->radioButtonUser->setChecked(true);   //默认选择用户


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeClient(){
    this->show();
    sw->hide();
}

void MainWindow::changeManage(){
    this->show();
    tw->hide();
}

//登录功能槽函数
void MainWindow::on_pushButtonLogin_clicked()
{
    QString username = ui->lineEditUserName->text();
    QString password = ui->lineEditPassword->text();
    if(username==""||password==""){  //输入为空
        QMessageBox::information(this, QStringLiteral("提醒"),QStringLiteral("请按照格式正确填写用户名和密码！"));
    }

    //0.连接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("localmysql"); //不是Database,记得别填错
    db.setUserName("root");
    db.setPassword("wujian143");
    bool ok = db.open();
    if (!ok){
        QMessageBox::information(this, "infor", "link failed");
        qDebug()<<"error open database because"<<db.lastError().text();
    }else{
        qDebug()<<"link success";
    }

    bool in=false;
    if(ui->radioButtonAdmin->isChecked()){    //进入管理员模块
        QSqlQuery selectQuery;
        QString sql = QString("select * from admin where admin_name = '%1' and admin_password='%2';").arg(username,password);
        in = selectQuery.exec(sql);
        if(!in)
        {
          qDebug()<<selectQuery.lastError();
        }
        if(selectQuery.next()){
            this->hide();
            g_username = username;
            g_password = password;
            tw = new manage;
            this->tw->show();
        }
        else{
            QMessageBox::information(this, QStringLiteral("提醒"),QStringLiteral("用户名或密码有误！！！"));
        }
    }
     //进入用户模块
    if(ui->radioButtonUser->isChecked()){
        QSqlQuery selectQuery;
        QString sql = QString("select * from user where user_name = '%1' and user_password='%2';").arg(username,password);
        in =selectQuery.exec(sql);
        if(!in)
        {
          qDebug()<<selectQuery.lastError();
        }
        if(selectQuery.next()){
            db.removeDatabase(db.connectionName());
            this->hide();
            g_username = username;
            g_password = password;
            sw = new client;
            this->sw->show();
        }
        else{
            QMessageBox::information(this, QStringLiteral("提醒"),QStringLiteral("用户名或密码有误！"));
        }
    }
}

//退出功能
void MainWindow::on_pushButtonExit_clicked()
{
    this->close();
}
