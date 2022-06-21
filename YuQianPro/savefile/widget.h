#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "contents.h"
#include "historyinfo.h"
#include "testpoint_info.h"
#include "homepage.h"

#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QUrlQuery>
#include <QDebug>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    QString getToken()
    {
        return strToken;
    }

private slots:
    void on_pushButton_clicked();

    int loginSuccess(QNetworkReply *reply);


signals:
    void send_datas(QString his_datas);
    void send_datas_down(QString his_datas);

private:
    Ui::Widget *ui;

    Contents *content;
    HistoryCharts *his;
    TestPoint_Info *test_info;
    HomePage *homepage_cope;

    //http部分
    QNetworkAccessManager * httpLogin;
    QString strToken;
    int projectCode;
    bool isLogin;
};

#endif // WIDGET_H
