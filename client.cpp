#include "client.h"
#include "ui_client.h"
#include "mainwindow.h"
#include "globle.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QString>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QItemSelectionModel>
#include <QModelIndexList>
#include <QMessageBox>
#include <QString>

client::client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::client)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowMinimizeButtonHint|Qt::WindowCloseButtonHint);
    connect(ui->pushButtonReturn,&QPushButton::clicked,this, &client::sendSignal);  //返回主页
    setWindowTitle(QStringLiteral("民航票务管理与售票系统"));

    if(QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else{
        //连接数据库
        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
        db.setHostName("127.0.0.1");
        db.setPort(3306);
        db.setDatabaseName("localmysql"); //不是Database,记得别填错
        db.setUserName("root");
        db.setPassword("wujian143");
        if (!db.open()){
            QMessageBox::information(this, "infor", "link failed");
            qDebug()<<"error open database because"<<db.lastError().text();
        }
    }
    model = new QSqlTableModel(this);
    model->setTable("flight");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit); //设置model的修改模式
    ui->labelReallyName->setText(g_username);
    ui->tableView->setModel(model);

    QString str = QString("name = '%1'").arg(g_username);
    ui->tableView->setSortingEnabled(true);

    model->select();    //显示表
    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("航班号"));
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("起点"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("终点"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("日期"));
    model->setHeaderData(4, Qt::Horizontal, QStringLiteral("起飞时间"));
    model->setHeaderData(5, Qt::Horizontal, QStringLiteral("到达时间"));
    model->setHeaderData(6, Qt::Horizontal, QStringLiteral("预设座位数"));
    model->setHeaderData(7, Qt::Horizontal, QStringLiteral("剩余座位数"));
    model->setHeaderData(8, Qt::Horizontal, QStringLiteral("票价"));
    model->setHeaderData(9, Qt::Horizontal, QStringLiteral("航班所属公司"));
}

client::~client()
{
    delete ui;
}

void client::sendSignal(){
    emit mySignal();
}

//返回功能
void client::on_pushButtonReturn_clicked()
{
    MainWindow *dh;
    this->hide();
    dh=new MainWindow;
    dh->show();
}


//购票功能
void client::on_pushButtonBuy_clicked()
{
    QString str_fid = ui->lineEditfid->text();      //获取需要订票的航班号
    QString str_num = ui->lineEditnum->text();      //票数
    QString str_name = ui->lineEditname->text();    //姓名
    QString str_uid = ui->lineEdituid->text();      //身份证
    QString str_safe = ui->lineEditsafe->text();    //保险
    QString str_time = "2021-09-10";
    QString value1="";
    QString value2="";
    QString value3="";
    if((str_fid .isEmpty() || str_num .isEmpty()|| str_name .isEmpty()|| str_uid.isEmpty()|| str_safe .isEmpty()))
    {
        QMessageBox::information(this, QStringLiteral("提醒"),QStringLiteral("购票前需要填写完整信息！"));
    }
    else
    {
        QMessageBox::warning(this,QStringLiteral("购票"),QStringLiteral("确定购票?"),QMessageBox::Yes,QMessageBox::No);
        int ok = QMessageBox::warning(this,QStringLiteral("支付"),QStringLiteral("交易中..."),QMessageBox::Yes,QMessageBox::No);
        if(ok == QMessageBox::Yes)
        {
           QSqlQuery sql_q;

           // 设置将要执行的SQL查询语句，:sname是要被绑定数据的位置
           sql_q.prepare("select * from flight where flight_id = :fid");
           sql_q.bindValue(":fid",str_fid);   // 绑定数据到指定的位置
           sql_q.exec();
           QSqlRecord rec =  sql_q.record();
           while(sql_q.next())
           {
               rec = sql_q.record();
               int flight_start_timecol = rec.indexOf("flight_start_time");
               int flight_end_timecol = rec.indexOf("flight_end_time");
               int flight_pricecol = rec.indexOf("flight_price");
               value1 = sql_q.value(flight_start_timecol).toString();
               value2 = sql_q.value(flight_end_timecol).toString();
               value3 = sql_q.value(flight_pricecol).toString();
               qDebug()<<"flight_start_time:"<<value1<<"\t"<<"flight_end_time:"<<value2<<"\t"<<"flight_price:"<<value3;
           }

            QString insert_sql = "insert into orders values (null,?, ?, ?, ?, ? , ?, ?, ?, ? )";  //增加记录
            sql_q.prepare(insert_sql);
            sql_q.addBindValue(str_fid);    //航班号
            sql_q.addBindValue(str_name);   //购票者姓名
            sql_q.addBindValue(str_uid);    //身份证号码
            sql_q.addBindValue(str_time);   //日期
            sql_q.addBindValue(value1);   //起飞时刻
            sql_q.addBindValue(value2);    //到达时刻
            sql_q.addBindValue(value3);   //票价
            sql_q.addBindValue(str_safe);   //是否保险
            sql_q.addBindValue(str_num);    //票数
            if(!sql_q.exec())
            {
                qDebug() << sql_q.lastError();
            }
            else
            {
                qDebug() << "inserted!";
            }

            //更新航班记录
            QSqlQuery sql_query;
            QString update_sql = "update flight set flight_remain = flight_remain - :order_num where flight_id = :order_flight_id";
            sql_query.prepare(update_sql);
            sql_query.bindValue(":order_flight_id", str_fid);
            sql_query.bindValue(":order_num", str_num);

            if(!sql_query.exec())
            {
                qDebug() << sql_query.lastError();
            }
            else
            {
                qDebug() << "updated!";
            }

            QMessageBox::warning(this,QStringLiteral("支付"),QStringLiteral("购票成功！"),QMessageBox::Yes);

            model->submitAll(); //提交
        } else {
            model->revertAll(); //撤销
        }
    }

}

//查询功能
void client::on_pushButtonAns_clicked()
{
    QString start = ui->lineEditStart->text();
    QString end = ui->lineEditEnd->text();
    QString date = ui->lineEditDate->text();
    if(start .isEmpty() || end .isEmpty() || date .isEmpty())
    {
        QMessageBox::information(this, QStringLiteral("提醒"),QStringLiteral("查询条件不完整！"));
    }
    else
    {
        QString str = QString("flight_start = '%1' and flight_end = '%2' and flight_date= '%3'").arg(start).arg(end).arg(date);
        model->setFilter(str);
        model->select();
    }
}

//刷新功能
void client::on_pushButtonFresh_clicked()
{
    model = new QSqlTableModel(this);
    model->setTable("flight");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit); //设置model的修改模式
    ui->labelReallyName->setText(g_username);
    ui->tableView->setModel(model);
    model->select();
    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("航班号"));
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("起点"));
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("终点"));
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("日期"));
    model->setHeaderData(4, Qt::Horizontal, QStringLiteral("起飞时间"));
    model->setHeaderData(5, Qt::Horizontal, QStringLiteral("到达时间"));
    model->setHeaderData(6, Qt::Horizontal, QStringLiteral("预设座位数"));
    model->setHeaderData(7, Qt::Horizontal, QStringLiteral("剩余座位数"));
    model->setHeaderData(8, Qt::Horizontal, QStringLiteral("票价"));
    model->setHeaderData(9, Qt::Horizontal, QStringLiteral("航班所属公司"));
}
