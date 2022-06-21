#ifndef CONTENTS_H
#define CONTENTS_H

#include <QWidget>
#include <QTableWidget>
#include <QObject>
#include <QTimer>
#include "historyinfo.h"
#include "testpoint_info.h"
#include "historycharts.h"

#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QUrlQuery>
#include <QDebug>
#include <QMap>
#include <QString>
#include <QDateTime>
#include "qcustomplot.h"
#include <QVector>


class HomePage;
typedef struct uapdat_data
{
    QString time;//实时时间
    double date; //实时数据
}Update_Date;


typedef struct saveInfo
{
    QString pointCode;//测点编号
    QString pointName;//测点名称
    QString factorName;//检测因素名称

    QString phy;
    QString datas;
    double the_data;
    QString data_time;
    QString unit;


}saveInfo;

namespace Ui {
class Contents;
}
class QTimer;
class Contents : public QWidget
{
    Q_OBJECT

public:
    explicit Contents(QWidget *parent = nullptr);
    ~Contents();



    void sendData(QString data); //在子窗口创建public函数用来获取传递的数据

    void set_conten_homet(HomePage* pwidget);



private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    //    void on_pushButton_4_clicked();

    //超时处理函数
    void handleTimeout();

    //    void on_pushButton_6_clicked();

    //    void on_pushButton_5_clicked();

    int loginSuccess(QNetworkReply *reply);

    void DisplayMsg();//槽函数

    //    void my_mouseMove(QMouseEvent* event);
    //    void select_click(int item);

    void on_pushButton_4_clicked();


    void Receive(QString Select_Info);//获取点击的得到的是哪个吊杆和测点

    //signals:
    //    void mouseMove(QMouseEvent*);



    void on_pushButton_5_clicked();

private:

    int update_data(QNetworkReply *reply);
    void update_plot();
    void update_plot(QCustomPlot *select_Widget,QVector<double> x1, QVector<double> y1,QVector<double> x2, QVector<double> y2);
    void update_plot(QCustomPlot *select_Widget,QVector<double> x1, QVector<double> y1,int dex);

    //绘制表格函数
    void table_up(QTableWidget *select_widget,QVector<QString> SaveTime, QVector<double> y1,int dex,QString The_Name);


    //画图函数
    void paint_on(QCustomPlot *widgets,QVector<double> num1(),QVector<double> num2(),int num_graph);

    //    void init_paint(QCustomPlot *widgets,double cut_timestamp1,const char * tab_name1,const char * tab_name2);

    void init_paint_one(QCustomPlot *widgets,double cut_timestamp1,const char * tab_name1);

private:
    Ui::Contents *ui;
    QTableWidget *tableWidget;
    HistoryInfo *historyinfo;
    QTimer *m_pTimer;
    TestPoint_Info *testpoint_info;
    HistoryCharts *historycharts;

    QNetworkAccessManager * httpLogin;
    QVector<double> x1,y1,x2,y2;
    QVector<QString>SaveTime;
    QString strToken1;
    int projectCode;
    bool isLogin;

    QString strToken;

    //    QVector<double> x_east_left;
    //    QVector<double> y_east_left;

    QCustomPlot* m_testPlot;

    //    QCustomPlot m_plot_west;//西右测点

    //    QMap<QString,Update_Date> m_map_upadate_data; //key :测点名称
    QString name;
    //
    HomePage *d;

};

#endif // CONTENTS_H
