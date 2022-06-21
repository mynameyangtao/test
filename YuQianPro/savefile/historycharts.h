#ifndef HISTORYCHARTS_H
#define HISTORYCHARTS_H

#include "qcustomplot.h"

#include <QObject>
#include <QTimer>
#include "historyinfo.h"
#include "testpoint_info.h"
//#include "contents.h"

#include <QWidget>

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
#include <QString>
#include <QFile>

typedef struct found_Info
{
    QString pointCode;//测点编号
    QString pointName;//测点名称
    QString factorName;//检测因素名称

    QString phy;
    QString datas;
    double the_data;
    QString data_time;
    QString unit;


}found_Info;

namespace Ui {
class HistoryCharts;
}

class HistoryCharts : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryCharts(QWidget *parent = nullptr);
    ~HistoryCharts();

    void send_Token_Data(QString Token_data); //在子窗口创建public函数用来获取传递的数据

    void saveMyData(QByteArray Mydata,QString Myname);

private slots:
    void on_pushButton_6_clicked();
    int loginSuccess(QNetworkReply *reply);

    void receive_data(QString rec_datas);

    void on_pushButton_5_clicked();

    void select_click(int item);

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();

private:
    int update_data(QNetworkReply *reply);
    void init_paint(QCustomPlot *widgets,double cut_timestamp1,const char * tab_name1,const char * tab_name2);

    void update_plot(QCustomPlot *select_Widget,QVector<double> x1, QVector<double> y1,int dex);
private:
    Ui::HistoryCharts *ui;
    QNetworkAccessManager * httpLogin;
    int projectCode;
    bool isLogin;
    QVector<double> x1,y1,x2,y2;
    QString strToken;
    //    QString info;
    QString str_all;
    QString End_str_all;

    QString short_str_all;
    QString short_End_str_all;

};

#endif // HISTORYCHARTS_H
