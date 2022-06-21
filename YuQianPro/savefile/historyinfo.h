#ifndef HISTORYINFO_H
#define HISTORYINFO_H

//class Contents;
#include <QWidget>
#include <QTableWidget>
#include <QDateTime>
#include <QTimer>
//#include "contents.h"

namespace Ui {
class HistoryInfo;
}

class HistoryInfo : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryInfo(QWidget *parent = nullptr);
    ~HistoryInfo();

    void setText(int i,QString status);

    void earn_data(float data_up[],float data_down[])
    {
        for(int i=0;i<8;i++)
        {
            data_up[i]=this->num[i];
            data_down[i]=this->num1[i];
        }
    }

protected:
    //    void run();

signals:
    void GetUdpLogMsg();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void handleTimeout();
private:
    Ui::HistoryInfo *ui;
    QTableWidget *tableWidget;

    float num[8];
    float num1[8];

    QTimer *m_pTimer;
    //    Contents *info_contents;

};

#endif // HISTORYINFO_H
