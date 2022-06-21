#ifndef TESTPOINT_INFO_H
#define TESTPOINT_INFO_H

#include <QWidget>
#include <QObject>

#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QUrlQuery>

#include <QAxObject>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>



namespace Ui {
class TestPoint_Info;
}

class TestPoint_Info : public QWidget
{
    Q_OBJECT

public:
    explicit TestPoint_Info(QWidget *parent = nullptr);
    ~TestPoint_Info();

    void down_receive_Data(QString data); //在子窗口创建public函数用来获取传递的数据

    void saveMyData_test(QByteArray Mydata,QString Myname);

    void skipSave_excl();


private slots:
    void on_pushButton_5_clicked();


    void receive_data_down(QString rec_datas);
    int loginSuccess(QNetworkReply *reply);

private:
    //    int update_data(QNetworkReply *reply);


private:
    Ui::TestPoint_Info *ui;

    QNetworkAccessManager * httpLogin;
    int projectCode;
    bool isLogin;

    QString str_all;
    QString End_str_all;

    QString short_str_all;
    QString short_End_str_all;

    QVector<QString> diaogan,shijian;
    QVector<double> wendu,yingbianzhi;

    int nub=0;
    int nub1=0;
    int nub2=0;
    int nub3=0;
    int nub4=0;
    int nub5=0;
    int nub6=0;
    int nub7=0;

    //.append()添加数据    .count 计算大小

    //    QString strToken_down;
};

#endif // TESTPOINT_INFO_H
