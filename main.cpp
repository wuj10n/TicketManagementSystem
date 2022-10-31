#include "mainwindow.h"
#include <QApplication>
#include <QString>
#include <QRadioButton>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //0.连接数据库
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
        db.setHostName("127.0.0.1");
        db.setPort(3306);
        db.setDatabaseName("localmysql"); //不是Database,记得别填错
        db.setUserName("root");
        db.setPassword("wujian143");
        bool ok = db.open();
        if (!ok){
            qDebug()<<"error open database because"<<db.lastError().text();
        }
    //对数据库进行初始化(仅第一次需要)
       QSqlQuery query;
        ok = query.exec("DROP TABLE IF EXISTS admin;");
        if(!ok)
        {
          qDebug() <<"Fail to delete previous table admin:" <<query.lastError();
        }else{
            qDebug() <<"drop previous table admin success";
          }

        ok=query.exec("DROP TABLE IF EXISTS user;");
        if(!ok)
        {
          qDebug() <<"Fail to delete previous table user:" <<query.lastError();
        }else{
            qDebug() <<"drop previous table user success";
          }
        ok=query.exec("DROP TABLE IF EXISTS flight;");
        if(!ok)
        {
          qDebug() <<"Fail to delete previous table flight:" <<query.lastError();
        }else{
          qDebug() <<"drop previous table flight success";
        }
        ok=query.exec("DROP TABLE IF EXISTS orders;");
        if(!ok)
        {
          qDebug() <<"Fail to delete previous table orders:" <<query.lastError();
        }else{
          qDebug() <<"drop previous table orders success";
        }

    //创建admin表
        ok =  query.exec("CREATE TABLE admin ("
                   "admin_id        int           NOT NULL AUTO_INCREMENT,"
                   "admin_name      char(50)      NOT NULL,"
                   "admin_password  char(32)      NOT NULL,"
                   "PRIMARY KEY (admin_id)"
                   ");");
       if(!ok)
       {
               qDebug() <<"Fail to create table admin:"<< query.lastError();
       }

    query.exec("INSERT INTO admin VALUES (null, 'admin', 'admin');");
    query.exec("INSERT INTO admin VALUES (null, 'admin2', 'admin2');");
    query.exec("INSERT INTO admin VALUES (null, 'admin3', 'admin3');");

    //创建usr表


    ok = query.exec("CREATE TABLE user ("
                    "user_id        int         NOT NULL AUTO_INCREMENT,"
                    "user_name      char(50)    NOT NULL,"
                    "user_password  char(32)    NOT NULL,"
                    "PRIMARY KEY (user_id)"
                    ");");
    if(!ok)
    {
        qDebug() << "Fail to create table user:"<<query.lastError();
    }
    query.exec(QStringLiteral("INSERT INTO user VALUES (null, '1001', '123456');"));
    query.exec(QStringLiteral("INSERT INTO user VALUES (null, '1002', '123456');"));
    query.exec(QStringLiteral("INSERT INTO user VALUES (null, '1003', '123456');"));

    //创建flight表

    ok =query.exec("CREATE TABLE flight ("
                 "flight_id            int NOT NULL,"              //航班号
                 "flight_start         text,"                      //起点
                 "flight_end           text,"                      //终点
                 "flight_date          text,"                      //日期
                 "flight_start_time    text,"                      //起飞时刻
                 "flight_end_time      text,"                      //到达时刻
                 "flight_seat          int,"                       //预设座位数
                 "flight_remain        int,"                       //剩余座位数
                 "flight_price         int, "                      //票价
                 "flight_company       text,"                      //所属公司
                 "PRIMARY KEY (flight_id )"
               ");");
    if(!ok)
    {
        qDebug() << "Fail to create table flight:"<<query.lastError();
    }



    query.exec(QStringLiteral("INSERT INTO flight VALUES ('1001','北京','上海','2021-11-03','12:10:00','13:20:00',100,100,500,'东方航空');"));
    query.exec(QStringLiteral("INSERT INTO flight VALUES ('1004','南京','重庆','2021-10-23','10:00:00','12:20:00',80,80,620,'南方航空');"));
    query.exec(QStringLiteral("INSERT INTO flight VALUES ('1002','北京','海口','2021-09-20','22:40:00','00:30:00',98,98,500,'国航');"));
    query.exec(QStringLiteral("INSERT INTO flight VALUES ('1005','天津','上海','2021-09-12','14:10:00','16:20:00',78,78,680,'东方航空');"));
    query.exec(QStringLiteral("INSERT INTO flight VALUES ('1003','海南','昆明','2021-09-10','08:00:00','08:55:00',60,60,800,'东方航空');"));
    query.exec(QStringLiteral("INSERT INTO flight VALUES ('1014','海南','黑龙江','2021-09-10','07:00:00','09:50:00',60,60,800,'南方航空');"));
    query.exec(QStringLiteral("INSERT INTO flight VALUES ('1009','上海','大连','2021-09-10','07:00:00','09:50:00',60,60,750,'海南航空');"));
    query.exec(QStringLiteral("INSERT INTO flight VALUES ('1019','成都','扬州','2021-09-10','07:10:00','09:50:00',60,60,700,'春秋航空');"));
    query.exec(QStringLiteral("INSERT INTO flight VALUES ('1021','海南','成都','2021-09-10','07:00:00','09:50:00',60,60,900,'春秋航空');"));
    query.exec(QStringLiteral("INSERT INTO flight VALUES ('1008','海南','大连','2021-09-10','07:00:00','09:50:00',60,60,800,'海南航空');"));
    query.exec(QStringLiteral("INSERT INTO flight VALUES ('1006','南京','南宁','2021-09-08','11:20:00','13:00:00',60,60,670,'东方航空');"));
    query.exec(QStringLiteral("INSERT INTO flight VALUES ('1007','深圳','上海','2021-10-02','20:30:00','21:40:00',87,87,580,'深圳航空');"));
    query.exec(QStringLiteral("INSERT INTO flight VALUES ('1010','宁波','广州','2021-09-14','09:00:00','10:20:00',90,90,700,'南方航空');"));
    query.exec(QStringLiteral("INSERT INTO flight VALUES ('1011','桂林','南京','2021-09-10','23:20:00','01:30:00',86,86,810,'东方航空');"));
    query.exec(QStringLiteral("INSERT INTO flight VALUES ('1012','扬州','广州','2021-09-15','08:00:00','10:20:00',99,99,600,'春秋航空');"));
    query.exec(QStringLiteral("INSERT INTO flight VALUES ('1013','扬州','广州','2021-09-16','08:00:00','10:20:00',99,99,600,'春秋航空');"));
    query.exec(QStringLiteral("INSERT INTO flight VALUES ('1015','北京','西宁','2021-09-20','22:40:00','00:30:00',98,98,670,'国航');"));
    query.exec(QStringLiteral("INSERT INTO flight VALUES ('1018','北京','海口','2021-09-21','22:40:00','00:30:00',98,98,800,'国航');"));
    query.exec(QStringLiteral("INSERT INTO flight VALUES ('1020','北京','青海','2021-09-22','22:40:00','00:30:00',98,98,520,'东方航空');"));
    query.exec(QStringLiteral("INSERT INTO flight VALUES ('1015','南京','桂林','2021-09-11','22:20:00','00:30:00',86,86,790,'东方航空');"));
    query.exec(QStringLiteral("INSERT INTO flight VALUES ('1016','深圳','大连','2021-09-10','07:00:00','09:50:00',60,60,800,'海南航空');"));
    query.exec(QStringLiteral("INSERT INTO flight VALUES ('1017','南京','北京','2021-09-00','11:20:00','13:00:00',60,60,670,'东方航空');"));
    query.exec(QStringLiteral("INSERT INTO flight VALUES ('1022','西安','南京','2021-10-02','19:30:00','21:40:00',87,87,780,'国航');"));


    //创建order表
    ok =  query.exec("CREATE TABLE orders ("
               "order_id                    int           NOT NULL AUTO_INCREMENT," //订单号
               "order_flight_id             int NOT NULL,"                          //航班号
               "order_person_name           char(50)      NOT NULL,"                 //购票者姓名
               "order_person_id             char(50)      NOT NULL,"                //身份证号码
               "order_date                  text,"                                  //日期
               "order_flight_start_time     text,"                                  //起飞时刻
               "order_flight_end_time       text,"                                  //到达时刻
               "order_flight_price          int,"                                  //票价
               "order_safe                  text,"                                  //是否保险
               "order_num                   int,"                                   //票数
               "PRIMARY KEY (order_id)"
               ");");
   if(!ok)
   {
       qDebug() << "Fail to create table order:"<<query.lastError();
   }
    db.close();
    MainWindow w;
    w.show();

    return a.exec();
}
