#include "historyinfo.h"
#include "ui_historyinfo.h"
#include <QHeaderView>
#include <QApplication>


#include <QDebug>

HistoryInfo::HistoryInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryInfo)
{
    ui->setupUi(this);

    //    m_contents=static_cast<Contents*>(parent);

    //定时器部分
    m_pTimer=new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    m_pTimer->start(500);

    //    m_pTimer->stop();


    //          info_contents=new Contents();

    //        tableWidget = new QTableWidget(this);


    //        ui->tableWidget->setRowCount(8);
    //        ui->tableWidget->setColumnCount(2);
    //        ui->tableWidget->setWindowTitle("QTableWidget & Item");
    //        ui->tableWidget->resize(600, 350);  //设置表格

    //        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //        QStringList header;
    //        header<<"测点名称"<<"应变变化值";   //表头
    //        ui->tableWidget->setHorizontalHeaderLabels(header);
    //        ui->tableWidget->setItem(0,0,new QTableWidgetItem("东右吊杆"));
    //        ui->tableWidget->setItem(1,0,new QTableWidgetItem("东右测点"));
    //        ui->tableWidget->setItem(2,0,new QTableWidgetItem("东左吊杆"));
    //        ui->tableWidget->setItem(3,0,new QTableWidgetItem("东左测点"));
    //        ui->tableWidget->setItem(4,0,new QTableWidgetItem("西右测点"));
    //        ui->tableWidget->setItem(5,0,new QTableWidgetItem("西左吊杆"));
    //        ui->tableWidget->setItem(6,0,new QTableWidgetItem("西左吊杆2"));
    //        ui->tableWidget->setItem(7,0,new QTableWidgetItem("西左测点"));

    //        //填充表格数据
    //        for(int i=0;i<8;i++)
    //        {
    //            ui->tableWidget->setItem(i,1,new QTableWidgetItem("数据1"));

    //        }

    //        ui->tableWidget->setItem(0,1,new QTableWidgetItem("35"));
    //        ui->tableWidget->setItem(1,1,new QTableWidgetItem("36"));
    //        ui->tableWidget->setItem(2,1,new QTableWidgetItem("32"));

    ui->tableWidget_2->setRowCount(8);
    ui->tableWidget_2->setColumnCount(2);
    ui->tableWidget_2->setWindowTitle("QTableWidget & Item");
    ui->tableWidget_2->resize(1000, 350);  //设置表格

    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QStringList header1;
    header1<<"测点名称"<<"报警";   //表头
    ui->tableWidget_2->setHorizontalHeaderLabels(header1);
    ui->tableWidget_2->setItem(0,0,new QTableWidgetItem("东1测点"));
    ui->tableWidget_2->setItem(1,0,new QTableWidgetItem("东2吊杆"));
    ui->tableWidget_2->setItem(2,0,new QTableWidgetItem("北7测点"));
    ui->tableWidget_2->setItem(3,0,new QTableWidgetItem("北8吊杆"));
    ui->tableWidget_2->setItem(4,0,new QTableWidgetItem("南3测点"));
    ui->tableWidget_2->setItem(5,0,new QTableWidgetItem("南4吊杆"));
    ui->tableWidget_2->setItem(6,0,new QTableWidgetItem("西5测点"));
    ui->tableWidget_2->setItem(7,0,new QTableWidgetItem("西6吊杆"));
    ui->tableWidget_2->horizontalHeader()->setStyleSheet( "QHeaderView::section {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\
                                                          stop:0 #00007f, stop: 0.5 #00007f,stop: 0.6 #00007f, stop:1 #00007f);color: white;}");


//设置行序列背景色
    ui->tableWidget_2->verticalHeader()->setStyleSheet( "QHeaderView::section {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\
                                              stop:0 #00007f, stop: 0.5 #00007f,stop: 0.6 #00007f, stop:1 #00007f);color: white;}");
//设置表格左上角相交单元格颜色
//导填充入数据
for(int i=0;i<8;i++)
{
    //            ui->tableWidget_2->setItem(i,1,new QTableWidgetItem("-1000"));
    //            ui->tableWidget_2->setItem(i,2,new QTableWidgetItem("1000"));
    ui->tableWidget_2->setItem(i,1,new QTableWidgetItem("正常"));
    //            ui->tableWidget_2->setItem(i,4,new QTableWidgetItem("36.5"));


}

    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
//        ui->tableWidget_2->setItem(0,1,new QTableWidgetItem("35"));
//        ui->tableWidget_2->setItem(1,1,new QTableWidgetItem("36"));
//        ui->tableWidget_2->setItem(2,1,new QTableWidgetItem("32"));
//        tableWidget->show();

}

HistoryInfo::~HistoryInfo()
{
    delete ui;
}

//void HistoryInfo::run()
//{
//    emit GetUdpLogMsg();

//}

void HistoryInfo::on_pushButton_clicked()
{
    m_pTimer->stop();
    ui->pushButton->setText("已暂停");
    qDebug()<<"设置1成功";
}

void HistoryInfo::on_pushButton_2_clicked()
{

    m_pTimer->start();
    ui->pushButton->setText("停止报警");
//    for(int i=0;i<8;i++)
//    {
//        QString str = ui->tableWidget_2->item(i,1)->text();//取出字符串
//        num[i] = str.toFloat();//转成int

//        qDebug()<<"输出的上限值为："<<ui->tableWidget_2->item(i,1)->text();
//        qDebug()<<"输出的值为："<<ui->tableWidget_2->item(i,1)->text().toFloat();
//        qDebug()<<"输出的上限值为："<<num[i];


//        QString str1 = ui->tableWidget_2->item(i,2)->text();//取出字符串
//        num1[i] = str.toFloat();//转成int
//    }



//    //    ui->tableWidget_2->item(row,column)->setText(QString("%1").arg(num));//写入

//    emit GetUdpLogMsg();
//    qDebug()<<"设置2成功";
}


void HistoryInfo::handleTimeout()//定时器槽函数实现
{

    for(int i=0;i<8;i++)
    {
        if(ui->tableWidget_2->item(i,1)->text()=="异常")
        {
            QApplication::beep();
        }

    }



}


void HistoryInfo::setText(int i,QString status)
{
    ui->tableWidget_2->setItem(i,1,new QTableWidgetItem(status));
}
