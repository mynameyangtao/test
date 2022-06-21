#include "contents.h"
#include "ui_contents.h"
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QIcon>
#include <QDebug>
#include <QString>
#include <QDateTime>
#include <QString>
#include <QStringList>
#include <QVector>
#include "widget.h"

//#include "homepage.h"

void Contents::sendData(QString data)
{
    strToken=data;
    qDebug()<<"传过来的数据是：2"<<strToken;
    handleTimeout();
}
//得到获取到的吊杆或测点是哪个
void Contents::Receive(QString Select_Info)
{
    name=Select_Info;

    if(name=="东1测点")
    {
        //设置对应显示的的ui->tabWidget_3->setCurrentIndex(dex)  tab
        ui->tabWidget_3->setCurrentIndex(0);
    }
    if(name=="东2吊杆")
    {
        //设置对应显示的的ui->tabWidget_3->setCurrentIndex(dex)  tab
        ui->tabWidget_3->setCurrentIndex(1);
    }
    if(name=="北7测点")
    {
        //设置对应显示的的ui->tabWidget_3->setCurrentIndex(dex)  tab
        ui->tabWidget_3->setCurrentIndex(2);
    }
    if(name=="北8吊杆")
    {
        //设置对应显示的的ui->tabWidget_3->setCurrentIndex(dex)  tab
        ui->tabWidget_3->setCurrentIndex(3);
    }
    if(name=="南3测点")
    {
        //设置对应显示的的ui->tabWidget_3->setCurrentIndex(dex)  tab
        ui->tabWidget_3->setCurrentIndex(4);
    }
    if(name=="南4吊杆")
    {
        //设置对应显示的的ui->tabWidget_3->setCurrentIndex(dex)  tab
        ui->tabWidget_3->setCurrentIndex(5);
    }
    if(name=="西5测点")
    {
        //设置对应显示的的ui->tabWidget_3->setCurrentIndex(dex)  tab
        ui->tabWidget_3->setCurrentIndex(6);
    }
    if(name=="西6吊杆")
    {
        //设置对应显示的的ui->tabWidget_3->setCurrentIndex(dex)  tab
        ui->tabWidget_3->setCurrentIndex(7);
    }

    //做出判断是哪一个，然后给标志位赋值，进行后续操作
}

//******************************************************************************************************************************************************
Contents::Contents(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Contents)
{
    ui->setupUi(this);
    setWindowTitle("德岭软件 v1.1");
    this->setFixedSize(1471,801);
    //***************************************************
    //获取信息 http链接
    isLogin = false;
    //    ui->pushButton_2->setEnabled(false);
    httpLogin = new QNetworkAccessManager(this);
    projectCode = 1552;
    // 绑定请求完成信号和完成后的操作
    connect(httpLogin, SIGNAL(finished(QNetworkReply *)), this, SLOT(loginSuccess(QNetworkReply *)));

    //设置表格不可更改
    //    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //    ui->tableWidget_1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_4->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_5->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_6->setEditTriggers(QAbstractItemView::NoEditTriggers);


    d=new HomePage();
    //根据实物图点击对应的按钮，做出相对应的显示操作
    //    QString diaogan_name=name;

    //        if(diaogan_name=="东1测点")
    //        {
    //            //设置对应显示的的ui->tabWidget_3->setCurrentIndex(dex)  tab
    //            ui->tabWidget_3->setCurrentIndex(0);
    //        }
    //        if(diaogan_name=="东2吊杆")
    //        {
    //            //设置对应显示的的ui->tabWidget_3->setCurrentIndex(dex)  tab
    //            ui->tabWidget_3->setCurrentIndex(1);
    //        }
    //        if(diaogan_name=="北7测点")
    //        {
    //            //设置对应显示的的ui->tabWidget_3->setCurrentIndex(dex)  tab
    //            ui->tabWidget_3->setCurrentIndex(2);
    //        }
    //        if(diaogan_name=="北8吊杆")
    //        {
    //            //设置对应显示的的ui->tabWidget_3->setCurrentIndex(dex)  tab
    //            ui->tabWidget_3->setCurrentIndex(3);
    //        }
    //        if(diaogan_name=="南3测点")
    //        {
    //            //设置对应显示的的ui->tabWidget_3->setCurrentIndex(dex)  tab
    //            ui->tabWidget_3->setCurrentIndex(4);
    //        }
    //        if(diaogan_name=="南4吊杆")
    //        {
    //            //设置对应显示的的ui->tabWidget_3->setCurrentIndex(dex)  tab
    //            ui->tabWidget_3->setCurrentIndex(5);
    //        }
    //        if(diaogan_name=="西5测点")
    //        {
    //            //设置对应显示的的ui->tabWidget_3->setCurrentIndex(dex)  tab
    //            ui->tabWidget_3->setCurrentIndex(6);
    //        }
    //        if(diaogan_name=="西6吊杆")
    //        {
    //            //设置对应显示的的ui->tabWidget_3->setCurrentIndex(dex)  tab
    //            ui->tabWidget_3->setCurrentIndex(7);
    //        }


    //    ui->tabWidget_3->setCurrentIndex(7);//切换到第一个tab

    //    下拉框设置文本归正（不错位）
    //    ui->comboBox->setView(new QListView());
    //    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(select_click(int)));

    //connect(ui->widget_3, SIGNAL(mouseMove(QMouseEvent*)), this, SLOT(my_mouseMove(QMouseEvent*)));

    //设置tabwidget标题背景
    ui->tabWidget_3->setAttribute(Qt::WA_StyledBackground);


        ui->tabWidget_3->tabBar()->close();
    //        setTabText(0,"结构应变历史变化曲线图");
    //        ui->tabWidget_3->setTabText(1,"结构应变历史变化数据表");



    ui->textEdit->setStyleSheet("border: none;");//去除框线
    ui->textEdit->setAttribute(Qt::WA_TranslucentBackground);//设置子kongjian为透明背景色


    //历史管理部分
    historycharts=new HistoryCharts(this);
    historycharts->move(this->x()+20,this->y()+110);
    historycharts->hide();

    //历史告警信息部分
    historyinfo=new HistoryInfo(this);
    historyinfo->move(this->x()+70,this->y()+100);
    historyinfo->hide();

    //    historyinfo->setText(2);//设定是否出现异常的提示

    //测点信息管理
    testpoint_info=new TestPoint_Info(this);
    testpoint_info->move(this->x()+100,this->y()+150);
    testpoint_info->hide();



    //    connect(historyinfo,SIGNAL(to_send()),this,SLOT(to_receive()));


    //定时器部分
    m_pTimer=new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(handleTimeout()));
    m_pTimer->start(60000);

    ui->widget->setObjectName("mainwidget");
    ui->widget->setStyleSheet("#mainwidget{border-image:url(:/back/image/mybackgroundimage.jpg)}");


    ui->tabWidget_3->setStyleSheet("QTabWidget:pane {border-top:0px solid #e8f3f9;background: transparent;}\
                                   QTabWidget#tabWidget{background-color:rgb(255,0,0);background:  transparent;}\
                                   QTabBar::tab{background-color:rgb(220,200,180);color:rgb(255,255,255);font:75 13pt '微软雅黑';background:  transparent;text-decoration: underline;}\
                                   QTabBar::tab::selected{background-color:rgb(0,100,200);color:rgb(255,255,255);font:75 14pt '微软雅黑';background:  transparent;text-decoration: underline;}");

                                   //    //表格自适应
                                   //    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                                   //    ui->tableWidget_2 ->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                                   //                                       ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                                   //    ui->tableWidget_4->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                                   //    ui->tableWidget_5->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                                   //    ui->tableWidget_6->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                                   //    ui->tableWidget_7->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                                   //    ui->tableWidget_8->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

                                   //告警表格
                                   //    QTableWidget *tableWidget = new QTableWidget(ui->widget_2);
                                   //    tableWidget->setGeometry(100,200,800,600);
                                   //    tableWidget->hide();

                                   QIcon icon1;
            icon1.addFile(":/back/image/green_img.png");//添加图形，将加载进来的资源进行保存
    ui->label->setText("正常");
    ui->IndicatorLight_3->setMinimumSize(63,63);
    ui->IndicatorLight_3->setMaximumSize(63,63);
    ui->IndicatorLight_3->setIcon(icon1);
    ui->IndicatorLight_3->setIconSize(QSize(48,48));


    //折线图显示部分
    //                                    ui->widget_3
    QDateTime Thetime1 = QDateTime::currentDateTime(); //获取当前时间
    double cut_timestamp1 = Thetime1.toTime_t(); //将当前时间转为时间戳




    //    渲染设置表格
    //    init_paint(ui->widget_3,cut_timestamp1,"东左测点","东右测点");//参数cut_timestamp1为时间轴范围设置
    //    init_paint(ui->widget_4,cut_timestamp1,"西左测点","西右测点");//参数cut_timestamp1为时间轴范围设置
    //    //    init_paint(ui->widget_5,cut_timestamp1,"西左吊杆","西右吊杆");//参数cut_timestamp1为时间轴范围设置
    //    //    init_paint(ui->widget_6,cut_timestamp1,"东左吊杆","东右吊杆");//参数cut_timestamp1为时间轴范围设置

    //    init_paint(ui->widget_7,cut_timestamp1,"东左吊杆","东右吊杆");//参数cut_timestamp1为时间轴范围设置
    //    init_paint(ui->widget_8,cut_timestamp1,"东左吊杆","东右吊杆");//参数cut_timestamp1为时间轴范围设置
    //    init_paint(ui->widget_9,cut_timestamp1,"东左吊杆","东右吊杆");//参数cut_timestamp1为时间轴范围设置
    //    init_paint(ui->widget_10,cut_timestamp1,"东左吊杆","东右吊杆");//参数cut_timestamp1为时间轴范围设置
    //    init_paint(ui->widget_11,cut_timestamp1,"东左吊杆","东右吊杆");//参数cut_timestamp1为时间轴范围设置
    //    init_paint(ui->widget_12,cut_timestamp1,"东左吊杆","东右吊杆");//参数cut_timestamp1为时间轴范围设置
    //                                         update_plot(ui->widget_4,x1,y1,1);


    init_paint_one(ui->widget_3,cut_timestamp1,"东1测点");//参数cut_timestamp1为时间轴范围设置
    init_paint_one(ui->widget_4,cut_timestamp1,"东2吊杆");//参数cut_timestamp1为时间轴范围设置
    init_paint_one(ui->widget_7,cut_timestamp1,"北7测点");//参数cut_timestamp1为时间轴范围设置
    init_paint_one(ui->widget_8,cut_timestamp1,"北8吊杆");//参数cut_timestamp1为时间轴范围设置
    init_paint_one(ui->widget_9,cut_timestamp1,"南3测点");//参数cut_timestamp1为时间轴范围设置
    init_paint_one(ui->widget_10,cut_timestamp1,"南4吊杆");//参数cut_timestamp1为时间轴范围设置
    init_paint_one(ui->widget_11,cut_timestamp1,"西5测点");//参数cut_timestamp1为时间轴范围设置
    init_paint_one(ui->widget_12,cut_timestamp1,"西6吊杆");//参数cut_timestamp1为时间轴范围设置


}

Contents::~Contents()
{
    delete ui;
}


//实现选择下拉框槽函数
//void Contents::select_click(int item)
//{
//    //    ui->comboBox->setCurrentIndex(item);
//    qDebug()<<"点击触发到这里的信息";

//    ui->comboBox->setCurrentIndex(item);
//    ui->tabWidget_3->setCurrentIndex(item);

//    //    if(ui->comboBox->currentText()=="挂篮东")
//    //    {
//    //        ui->tabWidget_3->setCurrentIndex(item);
//    //    }
//    //    if(ui->comboBox->currentText()=="挂篮西")
//    //    {
//    //        ui->tabWidget_3->setCurrentIndex(item);
//    //    }

//}

void Contents::DisplayMsg()
{
    //***************************************
    //通过信号与槽实现 拿取到对应的上下限值
    float shuju[8];
    float shuju1[8];
    historyinfo->earn_data(shuju,shuju1);
    for(int i=0;i<8;i++)
    {
        qDebug()<<"111111111111"<<shuju[i];
        qDebug()<<"222222222222"<<shuju1[i];
    }
    //把上下限值添加到对应的动态应变变化值中 再进行判断是否触发告警
    //****************************************

    //********************************************************************设置正常只是灯部分
    QIcon icon1;
    icon1.addFile(":/back/image/green_img.png");//添加图形，将加载进来的资源进行保存
    ui->label->setText("正常");
    ui->IndicatorLight_3->setMinimumSize(63,63);
    ui->IndicatorLight_3->setMaximumSize(63,63);
    ui->IndicatorLight_3->setIcon(icon1);
    ui->IndicatorLight_3->setIconSize(QSize(48,48));
    //***********************************************************************************
}


void Contents::init_paint_one(QCustomPlot *widgets,double cut_timestamp1,const char * tab_name1)
{

    widgets->xAxis->grid()->setVisible(false);//去除横坐标网格线
    widgets->yAxis->grid()->setVisible(false);

    //QCPAxisTickerDateTime 时间坐标轴 必须要用智能指针
    QSharedPointer<QCPAxisTickerDateTime> timer1(new QCPAxisTickerDateTime);

    //设置时间格式
    timer1->setDateTimeFormat("MM-dd hh:mm");

    //设置时间轴 一共几格
    timer1->setTickCount(4);

    QCPTextElement *m_title;
    widgets->plotLayout()->insertRow(0);

    widgets->legend->setVisible(true);
    widgets->legend->setBrush(QColor(255,255,255,0));
    widgets->legend->setTextColor('white');//标识字体颜色
    widgets->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignRight);

    //    widgets->setBackground(QBrush("white"));
    //    widgets->xAxis->setLabelColor(QColor(Qt::black));

    //    widgets->xAxis->setTickLabelColor(QColor(Qt::black));
    //    widgets->xAxis->setBasePen(QPen(QColor(Qt::black)));

    //    widgets->yAxis->setLabelColor(QColor(Qt::black));

    //    widgets->yAxis->setTickLabelColor(QColor(Qt::black));
    //    widgets->yAxis->setBasePen(QPen(QColor(Qt::black)));

    widgets->setBackground(QBrush("black"));
    widgets->xAxis->setLabelColor(QColor(Qt::white));

    widgets->xAxis->setTickLabelColor(QColor(Qt::white));
    widgets->xAxis->setBasePen(QPen(QColor(Qt::white)));

    widgets->yAxis->setLabelColor(QColor(Qt::white));

    widgets->yAxis->setTickLabelColor(QColor(Qt::white));
    widgets->yAxis->setBasePen(QPen(QColor(Qt::white)));


    m_title  = new QCPTextElement(ui->widget_3, "");
    widgets->plotLayout()->addElement(0, 0, m_title);
    widgets->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);      //可拖拽+可滚轮缩放
    widgets->legend->setVisible(true);                                //右上角指示曲线的缩略框
    widgets->xAxis->setLabel(QStringLiteral("时间（T）"));
    widgets->yAxis->setLabel(QStringLiteral("应变变化值"));

    widgets->xAxis->setTickLabelRotation(0);//横坐标值倾斜度

    timer1->setTickStepStrategy(QCPAxisTicker::tssMeetTickCount);

    widgets->xAxis->setTicker(timer1);




    //轴当前可见部分的范围
    //     widgets->xAxis->setRange(cut_timestamp1-1000,cut_timestamp1+1000);
    //     widgets->yAxis->setRange(0,400);

    widgets->addGraph();
    widgets->graph(0)->setPen(QPen(Qt::green));
    widgets->graph(0)->setName(tr(tab_name1));

}



//初始化图
//void Contents::init_paint(QCustomPlot *widgets,double cut_timestamp1,const char * tab_name1,const char * tab_name2)
//{
//    //    QDateTime Thetime1 = QDateTime::currentDateTime(); //获取当前时间
//    //    int cut_timestamp1 = Thetime1.toTime_t(); //将当前时间转为时间戳

//    //    widgets->setSubGridVisible(false);
//    widgets->xAxis->grid()->setVisible(false);//去除横坐标网格线
//    widgets->yAxis->grid()->setVisible(false);

//    //QCPAxisTickerDateTime 时间坐标轴 必须要用智能指针
//    QSharedPointer<QCPAxisTickerDateTime> timer1(new QCPAxisTickerDateTime);

//    //设置时间格式
//    timer1->setDateTimeFormat("MM-dd hh:mm");


//    //设置时间轴 一共几格
//    timer1->setTickCount(4);

//    QCPTextElement *m_title;
//    widgets->plotLayout()->insertRow(0);

//    widgets->legend->setVisible(true);
//    widgets->legend->setBrush(QColor(255,255,255,0));
//    widgets->legend->setTextColor('white');//标识字体颜色
//    widgets->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignRight);

//    //    widgets->setBackground(QBrush("white"));
//    //    widgets->xAxis->setLabelColor(QColor(Qt::black));

//    //    widgets->xAxis->setTickLabelColor(QColor(Qt::black));
//    //    widgets->xAxis->setBasePen(QPen(QColor(Qt::black)));

//    //    widgets->yAxis->setLabelColor(QColor(Qt::black));

//    //    widgets->yAxis->setTickLabelColor(QColor(Qt::black));
//    //    widgets->yAxis->setBasePen(QPen(QColor(Qt::black)));

//    widgets->setBackground(QBrush("black"));
//    widgets->xAxis->setLabelColor(QColor(Qt::white));

//    widgets->xAxis->setTickLabelColor(QColor(Qt::white));
//    widgets->xAxis->setBasePen(QPen(QColor(Qt::white)));

//    widgets->yAxis->setLabelColor(QColor(Qt::white));

//    widgets->yAxis->setTickLabelColor(QColor(Qt::white));
//    widgets->yAxis->setBasePen(QPen(QColor(Qt::white)));


//    m_title  = new QCPTextElement(ui->widget_3, "");
//    widgets->plotLayout()->addElement(0, 0, m_title);
//    widgets->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);      //可拖拽+可滚轮缩放
//    widgets->legend->setVisible(true);                                //右上角指示曲线的缩略框
//    widgets->xAxis->setLabel(QStringLiteral("时间（T）"));
//    widgets->yAxis->setLabel(QStringLiteral("应变变化值"));

//    widgets->xAxis->setTickLabelRotation(0);//横坐标值倾斜度

//    timer1->setTickStepStrategy(QCPAxisTicker::tssMeetTickCount);

//    widgets->xAxis->setTicker(timer1);




//    //轴当前可见部分的范围
//    //     widgets->xAxis->setRange(cut_timestamp1-1000,cut_timestamp1+1000);
//    //     widgets->yAxis->setRange(0,400);

//    widgets->addGraph();
//    widgets->addGraph();

//    widgets->graph(0)->setPen(QPen(Qt::green));
//    widgets->graph(1)->setPen(QPen(Qt::red));
//    widgets->graph(0)->setName(tr(tab_name1));
//    widgets->graph(1)->setName(tr(tab_name2));

//}


void Contents::handleTimeout()//定时器槽函数实现
{
    qDebug()<<"传过来是："<<strToken.toUtf8();
    qDebug()<<"Enter timeout processing function\n";
    //    ui->widget_3->graph(0)->data().data()->clear();//清除


    QUrl url("https://www.everiaction.com/IOT-ADAPTER-CUSTOM/es/point/getData");
    QUrlQuery query;
    query.addQueryItem("projectCode", QString::number(projectCode));//项目编号
    //    query.addQueryItem("pointCode", "test");//测点编号


    QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
    QString strtime = dateTime .toString("yyyy-MM-dd hh:mm");//格式化时间

    //    query.addQueryItem("beginDate", "2022-04-28 00:00:00.000");//开始时间
    query.addQueryItem("endDate", strtime);//结束时间
    query.addQueryItem("pageSize", "60");//返回数据条数
    //    query.addQueryItem("pageSize", "test");//排序方式
    url.setQuery(query.query());//

    // https需要的配置
    QNetworkRequest reqLogin;
    QSslConfiguration sslConf = reqLogin.sslConfiguration();
    sslConf.setPeerVerifyMode(QSslSocket::VerifyNone);
    sslConf.setProtocol(QSsl::TlsV1SslV3);
    reqLogin.setSslConfiguration(sslConf);
    //指定url
    reqLogin.setUrl(url);
    // 设置header
    //.toUtf8()
    reqLogin.setRawHeader("Authorization",strToken.toUtf8());//Authorization身份验证
    //发送数据
    httpLogin->get(reqLogin);





}




//获取传递来的信息
int Contents::loginSuccess(QNetworkReply *reply)
{
    //    qDebug()<<"进入到该函数";
    update_data(reply);
    //    update_plot();
}

int Contents::update_data(QNetworkReply *reply)
{


    if (reply->error() == QNetworkReply::NoError)
    {

        QString str = reply->readAll();
        if (str.isEmpty())
            return 0;
        // 解析Json字符串
        QJsonParseError error;
        QJsonDocument document = QJsonDocument::fromJson(str.toUtf8(), &error);
        // 字符串没有错误

        if (!document.isEmpty() && (error.error == QJsonParseError::NoError))
        {
            update_plot(ui->widget_4,x1,y1,1);
            qDebug()<<"$$$$$$$$$$$";
            // 转为Json对象
            QJsonObject json = document.object();
            // 取状态的值
            QJsonValue status = json.value("status");

            //TODO
            //            if  (status.toInt() != 200)
            //            {
            //                update_plot();
            //                return 0;
            //            }

            QJsonValue data = json.value("data");



            if(data!=NULL)
            {

                // 检查值是否存在
                //longin

                if (data.isObject())
                {

                    qDebug()<<"$$";
                    QJsonObject dataObj = data.toObject();
                    QJsonValue checkToken = dataObj.value("token");
                    QJsonValue projects = dataObj.value("projects");
                    QJsonArray  proArray;
                    if (projects.isArray())
                    {
                        proArray = projects.toArray();
                        projectCode = proArray.at(0).toObject().value("projectCode").toInt();
                    }
                    strToken = checkToken.toString();
                    qDebug() << "token:" << strToken;
                    qDebug() << "projectCode:" << projectCode;
                    qDebug() << "Login success !!!";
                    if (!strToken.isEmpty())
                    {
                        //                      ui->pushButton_2->setEnabled(true);
                        isLogin = true;
                        return 1;
                    }
                    else
                    {
                        qDebug() << "Login failure !!!";
                    }
                }
                else if (data.isArray())
                {

                    QString info_error="";
                    QString info_error1="";
                    qDebug()<<"进入到图形之后";
                    QJsonArray dataArr=data.toArray();

                    //                    qDebug()<<"收到的数据是："<<dataArr;

                    struct saveInfo MySave;
                    x1.clear();
                    y1.clear();
                    int sizes =dataArr.size();
                    for(int i=0;i<sizes;i++)
                    {

                        int dex=0;
                        int dex1=0;
                        int dex2=0;
                        int dex3=0;
                        int dex4=0;
                        int dex5=0;
                        int dex6=0;
                        int dex7=0;
                        MySave.pointCode=dataArr.at(i).toObject().value("pointCode").toString();
                        MySave.pointName=dataArr.at(i).toObject().value("pointName").toString();
                        MySave.factorName=dataArr.at(i).toObject().value("factorName").toString();
                        QJsonArray list_arr=dataArr.at(i).toObject().value("listPhys").toArray();
                        int size_list = list_arr.size();

                        //                        if(MySave.pointName=="东左测点")
                        if(MySave.pointName=="东1测点")
                        {

                            for(int j=0;j<size_list;j++)
                            {
                                MySave.phy=list_arr.at(j).toObject().value("phy").toString();
                                if(MySave.phy=="应变变化值")
                                {
                                    QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                    qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                    int my_num=sec_arr.size();
                                    dex=my_num;

                                    for(int s=0;s<my_num;s++)
                                    {
                                        SaveTime.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
                                        x1.push_back(QDateTime::fromString(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19), "yyyy-MM-dd hh:mm:ss").toTime_t());
                                        y1.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        double kd[60];
                                        kd[s] = sec_arr.at(s).toObject().value("data").toDouble();
                                        //if(sec_arr.at(s).toObject().value("data").toDouble()<-1000||sec_arr.at(s).toObject().value("data").toDouble()>1000)//判断全部数据是否有出现异常
                                        if((sec_arr.at(s).toObject().value("data").toDouble()<-1000||sec_arr.at(s).toObject().value("data").toDouble()>1000)&&(sec_arr.at(s+1).toObject().value("data").toDouble()<-1000||sec_arr.at(s+1).toObject().value("data").toDouble()>1000)&&(sec_arr.at(s+2).toObject().value("data").toDouble()<-1000||sec_arr.at(s+2).toObject().value("data").toDouble()>1000))//判断连着三条数据是否异常
//                                        if((sec_arr.at(s).toObject().value("data").toDouble()<-1||sec_arr.at(s).toObject().value("data").toDouble()>1)&&(sec_arr.at(s+1).toObject().value("data").toDouble()<-1||sec_arr.at(s+1).toObject().value("data").toDouble()>1)&&(sec_arr.at(s+2).toObject().value("data").toDouble()<-1||sec_arr.at(s+2).toObject().value("data").toDouble()>1))//判断连着三条数据是否异常
                                        {
                                            historyinfo->setText(0,"异常");
                                            info_error="东1测点异常";
                                            info_error1="东1测点异常"+sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19)+sec_arr.at(s).toObject().value("data").toString();
                                            info_error.append("时间是："+sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
//                                            info_error.append("数据是："+sec_arr.at(s).toObject().value("data").toString());
                                            ui->textEdit->setText(info_error);
                                            //********************************************************************设置异常指示灯部分
                                            QIcon icon2;
                                            icon2.addFile(":/back/image/red_img.jpg");//添加图形，将加载进来的资源进行保存
                                            ui->label->setText("异常");
                                            ui->IndicatorLight_3->setMinimumSize(63,63);
                                            ui->IndicatorLight_3->setMaximumSize(63,63);
                                            ui->IndicatorLight_3->setIcon(icon2);
                                            ui->IndicatorLight_3->setIconSize(QSize(48,48));
                                            //***********************************************************************************

                                        }
//                                      else if(-1000<sec_arr.at(s).toObject().value("data").toDouble()&& sec_arr.at(s).toObject().value("data").toDouble()<1000)
                                        else if(-1000<sec_arr.at(s).toObject().value("data").toDouble()&& sec_arr.at(s).toObject().value("data").toDouble()<1000)
                                        {
                                            //********************************************************************设置正常只是灯部分
                                            QIcon icon1;
                                            icon1.addFile(":/back/image/green_img.png");//添加图形，将加载进来的资源进行保存
                                            ui->label->setText("正常");
                                            ui->IndicatorLight_3->setMinimumSize(63,63);
                                            ui->IndicatorLight_3->setMaximumSize(63,63);
                                            ui->IndicatorLight_3->setIcon(icon1);
                                            ui->IndicatorLight_3->setIconSize(QSize(48,48));
                                            //***********************************************************************************
                                            historyinfo->setText(0,"正常");
                                        }
                                        //
                                    }
                                }


                            }

                            table_up(ui->tableWidget_9,SaveTime,y1,dex,"东1测点");
                            SaveTime.clear();
                            update_plot(ui->widget_3,x1,y1,0);
                            x1.clear();
                            y1.clear();
                        }

                        //                        if(MySave.pointName=="东右测点")
                        if(MySave.pointName=="东2吊杆")
                        {

                            for(int j=0;j<size_list;j++)
                            {
                                MySave.phy=list_arr.at(j).toObject().value("phy").toString();
                                if(MySave.phy=="应变变化值")
                                {
                                    QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                    qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                    int my_num=sec_arr.size();

                                    dex1=my_num;
                                    for(int s=0;s<my_num;s++)
                                    {
                                        SaveTime.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
                                        x1.push_back(QDateTime::fromString(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19), "yyyy-MM-dd hh:mm:ss").toTime_t());
                                        y1.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        if((sec_arr.at(s).toObject().value("data").toDouble()<-1000||sec_arr.at(s).toObject().value("data").toDouble()>1000)&&(sec_arr.at(s+1).toObject().value("data").toDouble()<-1000||sec_arr.at(s+1).toObject().value("data").toDouble()>1000)&&(sec_arr.at(s+2).toObject().value("data").toDouble()<-1000||sec_arr.at(s+2).toObject().value("data").toDouble()>1000))//判断连着三条数据是否异常
                                        {
//                                            historyinfo->setText(0,"异常");
                                            info_error="东2测点异常";
                                            info_error1="东2测点异常"+sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19)+sec_arr.at(s).toObject().value("data").toString();
                                            info_error.append("时间是："+sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
//                                            info_error.append("数据是："+sec_arr.at(s).toObject().value("data").toString());
                                            ui->textEdit->setText(info_error);
                                            //********************************************************************设置异常指示灯部分
                                            QIcon icon2;
                                            icon2.addFile(":/back/image/red_img.jpg");//添加图形，将加载进来的资源进行保存
                                            ui->label->setText("异常");
                                            ui->IndicatorLight_3->setMinimumSize(63,63);
                                            ui->IndicatorLight_3->setMaximumSize(63,63);
                                            ui->IndicatorLight_3->setIcon(icon2);
                                            ui->IndicatorLight_3->setIconSize(QSize(48,48));
                                            //***********************************************************************************
                                            historyinfo->setText(1,"异常");
                                        }
                                        else if(-1000<sec_arr.at(s).toObject().value("data").toDouble( )&& sec_arr.at(s).toObject().value("data").toDouble()<1000){
                                            //********************************************************************设置正常只是灯部分
                                            QIcon icon1;
                                            icon1.addFile(":/back/image/green_img.png");//添加图形，将加载进来的资源进行保存
                                            ui->label->setText("正常");
                                            ui->IndicatorLight_3->setMinimumSize(63,63);
                                            ui->IndicatorLight_3->setMaximumSize(63,63);
                                            ui->IndicatorLight_3->setIcon(icon1);
                                            ui->IndicatorLight_3->setIconSize(QSize(48,48));
                                            //***********************************************************************************
                                            historyinfo->setText(1,"正常");
                                        }
                                    }
                                }


                            }
                            table_up(ui->tableWidget_8,SaveTime,y1,dex1,"东2吊杆");
                            SaveTime.clear();
                            update_plot(ui->widget_4,x1,y1,0);
                            x1.clear();
                            y1.clear();

                        }

                        //                        if(MySave.pointName=="东左吊杆")
                        if(MySave.pointName=="北7测点")
                        {

                            for(int j=0;j<size_list;j++)
                            {
                                MySave.phy=list_arr.at(j).toObject().value("phy").toString();
                                if(MySave.phy=="应变变化值")
                                {
                                    QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                    qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                    int my_num=sec_arr.size();

                                    dex2=my_num;
                                    for(int s=0;s<my_num;s++)
                                    {
                                        SaveTime.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
                                        x1.push_back(QDateTime::fromString(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19), "yyyy-MM-dd hh:mm:ss").toTime_t());
                                        y1.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        if((sec_arr.at(s).toObject().value("data").toDouble()<-1000||sec_arr.at(s).toObject().value("data").toDouble()>1000)&&(sec_arr.at(s+1).toObject().value("data").toDouble()<-1000||sec_arr.at(s+1).toObject().value("data").toDouble()>1000)&&(sec_arr.at(s+2).toObject().value("data").toDouble()<-1000||sec_arr.at(s+2).toObject().value("data").toDouble()>1000))//判断连着三条数据是否异常
                                        {
//                                            historyinfo->setText(0,"异常");
                                            info_error="北7测点异常";
                                            info_error1="北7测点异常"+sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19)+sec_arr.at(s).toObject().value("data").toString();
                                            info_error.append("时间是："+sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
//                                            info_error.append("数据是："+sec_arr.at(s).toObject().value("data").toString());
                                            ui->textEdit->setText(info_error);
                                            //********************************************************************设置异常指示灯部分
                                            QIcon icon2;
                                            icon2.addFile(":/back/image/red_img.jpg");//添加图形，将加载进来的资源进行保存
                                            ui->label->setText("异常");
                                            ui->IndicatorLight_3->setMinimumSize(63,63);
                                            ui->IndicatorLight_3->setMaximumSize(63,63);
                                            ui->IndicatorLight_3->setIcon(icon2);
                                            ui->IndicatorLight_3->setIconSize(QSize(48,48));
                                            //***********************************************************************************
                                            historyinfo->setText(2,"异常");
                                        }
                                        else if(-1000<sec_arr.at(s).toObject().value("data").toDouble( )&& sec_arr.at(s).toObject().value("data").toDouble()<1000){
                                            //********************************************************************设置正常只是灯部分
                                            QIcon icon1;
                                            icon1.addFile(":/back/image/green_img.png");//添加图形，将加载进来的资源进行保存
                                            ui->label->setText("正常");
                                            ui->IndicatorLight_3->setMinimumSize(63,63);
                                            ui->IndicatorLight_3->setMaximumSize(63,63);
                                            ui->IndicatorLight_3->setIcon(icon1);
                                            ui->IndicatorLight_3->setIconSize(QSize(48,48));
                                            //***********************************************************************************
                                            historyinfo->setText(2,"正常");
                                        }
                                    }
                                }


                            }
                            table_up(ui->tableWidget,SaveTime,y1,dex2,"北7测点");
                            SaveTime.clear();
                            update_plot(ui->widget_7,x1,y1,0);
                            x1.clear();
                            y1.clear();
                        }

                        //                        if(MySave.pointName=="东右吊杆")
                        if(MySave.pointName=="北8吊杆")
                        {

                            for(int j=0;j<size_list;j++)
                            {
                                MySave.phy=list_arr.at(j).toObject().value("phy").toString();
                                if(MySave.phy=="应变变化值")
                                {
                                    QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                    qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                    int my_num=sec_arr.size();
                                    dex3=my_num;

                                    for(int s=0;s<my_num;s++)
                                    {
                                        SaveTime.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
                                        x1.push_back(QDateTime::fromString(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19), "yyyy-MM-dd hh:mm:ss").toTime_t());
                                        y1.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        if((sec_arr.at(s).toObject().value("data").toDouble()<-1000||sec_arr.at(s).toObject().value("data").toDouble()>1000)&&(sec_arr.at(s+1).toObject().value("data").toDouble()<-1000||sec_arr.at(s+1).toObject().value("data").toDouble()>1000)&&(sec_arr.at(s+2).toObject().value("data").toDouble()<-1000||sec_arr.at(s+2).toObject().value("data").toDouble()>1000))//判断连着三条数据是否异常
                                        {
//                                            historyinfo->setText(0,"异常");
                                            info_error="北8测点异常";
                                            info_error1="北8测点异常"+sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19)+sec_arr.at(s).toObject().value("data").toString();
                                            info_error.append("时间是："+sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
//                                            info_error.append("数据是："+sec_arr.at(s).toObject().value("data").toString());
                                            ui->textEdit->setText(info_error);
                                            //********************************************************************设置异常指示灯部分
                                            QIcon icon2;
                                            icon2.addFile(":/back/image/red_img.jpg");//添加图形，将加载进来的资源进行保存
                                            ui->label->setText("异常");
                                            ui->IndicatorLight_3->setMinimumSize(63,63);
                                            ui->IndicatorLight_3->setMaximumSize(63,63);
                                            ui->IndicatorLight_3->setIcon(icon2);
                                            ui->IndicatorLight_3->setIconSize(QSize(48,48));
                                            //***********************************************************************************
                                            historyinfo->setText(3,"异常");
                                        }
                                        else if(-1000<sec_arr.at(s).toObject().value("data").toDouble( )&& sec_arr.at(s).toObject().value("data").toDouble()<1000){
                                            //********************************************************************设置正常只是灯部分
                                            QIcon icon1;
                                            icon1.addFile(":/back/image/green_img.png");//添加图形，将加载进来的资源进行保存
                                            ui->label->setText("正常");
                                            ui->IndicatorLight_3->setMinimumSize(63,63);
                                            ui->IndicatorLight_3->setMaximumSize(63,63);
                                            ui->IndicatorLight_3->setIcon(icon1);
                                            ui->IndicatorLight_3->setIconSize(QSize(48,48));
                                            //***********************************************************************************
                                            historyinfo->setText(3,"正常");
                                        }
                                    }
                                }


                            }
                            table_up(ui->tableWidget_2,SaveTime,y1,dex3,"北8吊杆");
                            SaveTime.clear();
                            update_plot(ui->widget_8,x1,y1,0);
                            x1.clear();
                            y1.clear();

                        }


                        // if(MySave.pointName=="西左测点")
                        if(MySave.pointName=="南3测点")
                        {

                            for(int j=0;j<size_list;j++)
                            {
                                MySave.phy=list_arr.at(j).toObject().value("phy").toString();
                                if(MySave.phy=="应变变化值")
                                {
                                    QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                    qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                    int my_num=sec_arr.size();
                                    dex4=my_num;

                                    for(int s=0;s<my_num;s++)
                                    {
                                        SaveTime.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
                                        x1.push_back(QDateTime::fromString(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19), "yyyy-MM-dd hh:mm:ss").toTime_t());
                                        y1.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        if((sec_arr.at(s).toObject().value("data").toDouble()<-1000||sec_arr.at(s).toObject().value("data").toDouble()>1000)&&(sec_arr.at(s+1).toObject().value("data").toDouble()<-1000||sec_arr.at(s+1).toObject().value("data").toDouble()>1000)&&(sec_arr.at(s+2).toObject().value("data").toDouble()<-1000||sec_arr.at(s+2).toObject().value("data").toDouble()>1000))//判断连着三条数据是否异常
                                        {
//                                            historyinfo->setText(0,"异常");
                                            info_error="南3测点异常";
                                            info_error1="南3测点异常"+sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19)+sec_arr.at(s).toObject().value("data").toString();
                                            info_error.append("时间是："+sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
//                                            info_error.append("数据是："+sec_arr.at(s).toObject().value("data").toString());
                                            ui->textEdit->setText(info_error);
                                            //********************************************************************设置异常指示灯部分
                                            QIcon icon2;
                                            icon2.addFile(":/back/image/red_img.jpg");//添加图形，将加载进来的资源进行保存
                                            ui->label->setText("异常");
                                            ui->IndicatorLight_3->setMinimumSize(63,63);
                                            ui->IndicatorLight_3->setMaximumSize(63,63);
                                            ui->IndicatorLight_3->setIcon(icon2);
                                            ui->IndicatorLight_3->setIconSize(QSize(48,48));
                                            //***********************************************************************************
                                            historyinfo->setText(4,"异常");
                                        }
                                        else if(-1000<sec_arr.at(s).toObject().value("data").toDouble( )&& sec_arr.at(s).toObject().value("data").toDouble()<1000){
                                            //********************************************************************设置正常只是灯部分
                                            QIcon icon1;
                                            icon1.addFile(":/back/image/green_img.png");//添加图形，将加载进来的资源进行保存
                                            ui->label->setText("正常");
                                            ui->IndicatorLight_3->setMinimumSize(63,63);
                                            ui->IndicatorLight_3->setMaximumSize(63,63);
                                            ui->IndicatorLight_3->setIcon(icon1);
                                            ui->IndicatorLight_3->setIconSize(QSize(48,48));
                                            //***********************************************************************************
                                            historyinfo->setText(4,"正常");
                                        }
                                    }
                                }


                            }
                            table_up(ui->tableWidget_3,SaveTime,y1,dex4,"南3测点");
                            SaveTime.clear();
                            update_plot(ui->widget_9,x1,y1,0);

                            x1.clear();
                            y1.clear();
                        }



                        //if(MySave.pointName=="西右测点")
                        if(MySave.pointName=="南4吊杆")
                        {

                            for(int j=0;j<size_list;j++)
                            {
                                MySave.phy=list_arr.at(j).toObject().value("phy").toString();
                                if(MySave.phy=="应变变化值")
                                {
                                    QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                    qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                    int my_num=sec_arr.size();
                                    dex5=my_num;

                                    for(int s=0;s<my_num;s++)
                                    {
                                        SaveTime.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
                                        x1.push_back(QDateTime::fromString(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19), "yyyy-MM-dd hh:mm:ss").toTime_t());
                                        y1.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        if((sec_arr.at(s).toObject().value("data").toDouble()<-1000||sec_arr.at(s).toObject().value("data").toDouble()>1000)&&(sec_arr.at(s+1).toObject().value("data").toDouble()<-1000||sec_arr.at(s+1).toObject().value("data").toDouble()>1000)&&(sec_arr.at(s+2).toObject().value("data").toDouble()<-1000||sec_arr.at(s+2).toObject().value("data").toDouble()>1000))//判断连着三条数据是否异常
                                        {
//                                            historyinfo->setText(0,"异常");
                                            info_error="南4测点异常";
                                            info_error1="南4测点异常"+sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19)+sec_arr.at(s).toObject().value("data").toString();
                                            info_error.append("时间是："+sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
//                                            info_error.append("数据是："+sec_arr.at(s).toObject().value("data").toString());
                                            ui->textEdit->setText(info_error);
                                            //********************************************************************设置异常指示灯部分
                                            QIcon icon2;
                                            icon2.addFile(":/back/image/red_img.jpg");//添加图形，将加载进来的资源进行保存
                                            ui->label->setText("异常");
                                            ui->IndicatorLight_3->setMinimumSize(63,63);
                                            ui->IndicatorLight_3->setMaximumSize(63,63);
                                            ui->IndicatorLight_3->setIcon(icon2);
                                            ui->IndicatorLight_3->setIconSize(QSize(48,48));
                                            //***********************************************************************************
                                            historyinfo->setText(5,"异常");
                                        }
                                        else if(-1000<sec_arr.at(s).toObject().value("data").toDouble( )&& sec_arr.at(s).toObject().value("data").toDouble()<1000){
                                            //********************************************************************设置正常只是灯部分
                                            QIcon icon1;
                                            icon1.addFile(":/back/image/green_img.png");//添加图形，将加载进来的资源进行保存
                                            ui->label->setText("正常");
                                            ui->IndicatorLight_3->setMinimumSize(63,63);
                                            ui->IndicatorLight_3->setMaximumSize(63,63);
                                            ui->IndicatorLight_3->setIcon(icon1);
                                            ui->IndicatorLight_3->setIconSize(QSize(48,48));
                                            //***********************************************************************************
                                            historyinfo->setText(5,"正常");
                                        }
                                    }
                                }


                            }
                            table_up(ui->tableWidget_4,SaveTime,y1,dex5,"南4吊杆");
                            SaveTime.clear();
                            update_plot(ui->widget_10,x1,y1,0);
                            x1.clear();
                            y1.clear();
                        }


                        //if(MySave.pointName=="西左吊杆")
                        if(MySave.pointName=="西5测点")
                        {

                            for(int j=0;j<size_list;j++)
                            {
                                MySave.phy=list_arr.at(j).toObject().value("phy").toString();
                                if(MySave.phy=="应变变化值")
                                {
                                    QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                    qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                    int my_num=sec_arr.size();
                                    dex6=my_num;

                                    for(int s=0;s<my_num;s++)
                                    {
                                        SaveTime.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
                                        x1.push_back(QDateTime::fromString(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19), "yyyy-MM-dd hh:mm:ss").toTime_t());
                                        y1.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        if((sec_arr.at(s).toObject().value("data").toDouble()<-1000||sec_arr.at(s).toObject().value("data").toDouble()>1000)&&(sec_arr.at(s+1).toObject().value("data").toDouble()<-1000||sec_arr.at(s+1).toObject().value("data").toDouble()>1000)&&(sec_arr.at(s+2).toObject().value("data").toDouble()<-1000||sec_arr.at(s+2).toObject().value("data").toDouble()>1000))//判断连着三条数据是否异常
                                        {
                                            historyinfo->setText(0,"异常");
                                            info_error="西5测点异常";
                                            info_error1="西5测点异常"+sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19)+sec_arr.at(s).toObject().value("data").toString();
                                            info_error.append("时间是："+sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
//                                            info_error.append("数据是："+sec_arr.at(s).toObject().value("data").toString());
                                            ui->textEdit->setText(info_error);
                                            //********************************************************************设置异常指示灯部分
                                            QIcon icon2;
                                            icon2.addFile(":/back/image/red_img.jpg");//添加图形，将加载进来的资源进行保存
                                            ui->label->setText("异常");
                                            ui->IndicatorLight_3->setMinimumSize(63,63);
                                            ui->IndicatorLight_3->setMaximumSize(63,63);
                                            ui->IndicatorLight_3->setIcon(icon2);
                                            ui->IndicatorLight_3->setIconSize(QSize(48,48));
                                            //***********************************************************************************
                                            historyinfo->setText(6,"异常");
                                        }
                                        else if(-1000<sec_arr.at(s).toObject().value("data").toDouble( )&& sec_arr.at(s).toObject().value("data").toDouble()<1000){
                                            //********************************************************************设置正常只是灯部分
                                            QIcon icon1;
                                            icon1.addFile(":/back/image/green_img.png");//添加图形，将加载进来的资源进行保存
                                            ui->label->setText("正常");
                                            ui->IndicatorLight_3->setMinimumSize(63,63);
                                            ui->IndicatorLight_3->setMaximumSize(63,63);
                                            ui->IndicatorLight_3->setIcon(icon1);
                                            ui->IndicatorLight_3->setIconSize(QSize(48,48));
                                            //***********************************************************************************
                                            historyinfo->setText(6,"正常");
                                        }
                                    }
                                }


                            }
                            table_up(ui->tableWidget_5,SaveTime,y1,dex6,"西5测点");
                            SaveTime.clear();
                            update_plot(ui->widget_11,x1,y1,0);
                            x1.clear();
                            y1.clear();
                        }




                        //if(MySave.pointName=="西右吊杆")
                        if(MySave.pointName=="西6吊杆")
                        {

                            for(int j=0;j<size_list;j++)
                            {
                                MySave.phy=list_arr.at(j).toObject().value("phy").toString();
                                if(MySave.phy=="应变变化值")
                                {
                                    QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                    qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                    int my_num=sec_arr.size();
                                    dex7=my_num;

                                    for(int s=0;s<my_num;s++)
                                    {
                                        SaveTime.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
                                        x1.push_back(QDateTime::fromString(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19), "yyyy-MM-dd hh:mm:ss").toTime_t());
                                        y1.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        if((sec_arr.at(s).toObject().value("data").toDouble()<-1000||sec_arr.at(s).toObject().value("data").toDouble()>1000)&&(sec_arr.at(s+1).toObject().value("data").toDouble()<-1000||sec_arr.at(s+1).toObject().value("data").toDouble()>1000)&&(sec_arr.at(s+2).toObject().value("data").toDouble()<-1000||sec_arr.at(s+2).toObject().value("data").toDouble()>1000))//判断连着三条数据是否异常
                                        {
//                                            historyinfo->setText(0,"异常");
                                            info_error="西6测点异常";
                                            info_error1="西6测点异常"+sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19)+sec_arr.at(s).toObject().value("data").toString();
                                            info_error.append("时间是："+sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
//                                            info_error.append("数据是："+sec_arr.at(s).toObject().value("data").toString());
                                            ui->textEdit->setText(info_error);
                                            //********************************************************************设置异常指示灯部分
                                            QIcon icon2;
                                            icon2.addFile(":/back/image/red_img.jpg");//添加图形，将加载进来的资源进行保存
                                            ui->label->setText("异常");
                                            ui->IndicatorLight_3->setMinimumSize(63,63);
                                            ui->IndicatorLight_3->setMaximumSize(63,63);
                                            ui->IndicatorLight_3->setIcon(icon2);
                                            ui->IndicatorLight_3->setIconSize(QSize(48,48));
                                            //***********************************************************************************
                                            historyinfo->setText(7,"异常");
                                        }
                                        else if(-1000<sec_arr.at(s).toObject().value("data").toDouble( )&& sec_arr.at(s).toObject().value("data").toDouble()<1000){
                                            //********************************************************************设置正常只是灯部分
                                            QIcon icon1;
                                            icon1.addFile(":/back/image/green_img.png");//添加图形，将加载进来的资源进行保存
                                            ui->label->setText("正常");
                                            ui->IndicatorLight_3->setMinimumSize(63,63);
                                            ui->IndicatorLight_3->setMaximumSize(63,63);
                                            ui->IndicatorLight_3->setIcon(icon1);
                                            ui->IndicatorLight_3->setIconSize(QSize(48,48));
                                            //***********************************************************************************
                                            historyinfo->setText(7,"正常");
                                        }
                                    }
                                }


                            }
                            table_up(ui->tableWidget_6,SaveTime,y1,dex7,"西6吊杆");
                            //update_plot(ui->widget_5,x1,y1,1);
                            update_plot(ui->widget_12,x1,y1,0);
                            SaveTime.clear();
                            x1.clear();
                            y1.clear();
                        }


                    }

                }
            }
            //            update_plot();


        }
    }


}

void Contents::table_up(QTableWidget *select_widget,QVector<QString> SaveTime, QVector<double> y1,int dex,QString The_Name)
{
    //****************************************************************************************表格测试
    select_widget->setRowCount(dex);
    select_widget->setColumnCount(3);
    select_widget->setWindowTitle("QTableWidget & Item");
    select_widget->resize(621, 461);  //设置表格

    select_widget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    select_widget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);

    select_widget->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
    //    select_widget->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
    QStringList header1;
    header1<<"时间"<<"测点名称"<<"应变变化值";   //表头

    //设置列序列背景色
    select_widget->horizontalHeader()->setStyleSheet( "QHeaderView::section {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\
                                                      stop:0 #00007f, stop: 0.5 #00007f,stop: 0.6 #00007f, stop:1 #00007f);color: white;}");
    //设置行序列背景色
    select_widget->verticalHeader()->setStyleSheet( "QHeaderView::section {background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,\
                                                  stop:0 #00007f, stop: 0.5 #00007f,stop: 0.6 #00007f, stop:1 #00007f);color: white;}");
   //设置表格左上角相交单元格颜色
//    select_widget->setStyleSheet("QTableCornerButton::section{background:yellow;}");

    select_widget->setHorizontalHeaderLabels(header1);
//    select_widget->setItem(0,0,new QTableWidgetItem("东1测点"));


//导填充入数据
for(int i=0;i<dex;i++)
{
    //        select_widget->setItem(i,0,new QTableWidgetItem(x1[i]));
    //        select_widget->setItem(i,1,new QTableWidgetItem(The_Name));
    //        select_widget->setItem(i,2,new QTableWidgetItem(y1[i]));

    select_widget->setItem(i,0,new QTableWidgetItem(SaveTime[i]));
    select_widget->setItem(i,1,new QTableWidgetItem(The_Name));
    select_widget->setItem(i,2,new QTableWidgetItem(QString::number(y1[i], 'f', 1)));
    //        select_widget->setItem(i,4,new QTableWidgetItem("36.5"));

}
}
//把数据添加到图上

void Contents::update_plot(QCustomPlot *select_Widget,QVector<double> x1, QVector<double> y1,int dex)
{

    //        select_Widget->graph(dex)->addData(1,1);
    //        select_Widget->graph(dex)->addData(2,2);
    //        select_Widget->graph(dex)->addData(5,5);
    //        select_Widget->graph(dex)->addData(9,9);
    //        select_Widget->graph(dex)->addData(15,15);
    //        select_Widget->xAxis->setRange(0,20);
    //        select_Widget->yAxis->setRange(0,20);


    //轴当前可见部分的范围
    QDateTime Thetime1 = QDateTime::currentDateTime(); //获取当前时间
    double cut_timestamp1 = Thetime1.toTime_t(); //将当前时间转为时间戳

    QVector<double> tempx,tempy;
    tempx.clear();
    tempy.clear();
    tempx = x1;
    tempy = y1;
    if (tempx.isEmpty())
    {
        return;
    }

    select_Widget->xAxis->setRange(x1[0],x1[0]+3600);
    select_Widget->yAxis->setRange(y1[0]-100,y1[0]+100);

    select_Widget->graph(dex)->addData(x1,y1);
    select_Widget->replot();



}

//鼠标移动操作
//void Contents::my_mouseMove(QMouseEvent* event)
//{
//    //获取鼠标坐标点
//        int x_pos = event->pos().x();
//        int y_pos = event->pos().y();

//    // 把鼠标坐标点 转换为 QCustomPlot 内部坐标值 （pixelToCoord 函数）
//    // coordToPixel 函数与之相反 是把内部坐标值 转换为外部坐标点
//        float x_val = ui->widget_3->xAxis->pixelToCoord(x_pos);
//        float y_val = ui->widget_3->yAxis->pixelToCoord(y_pos);

//    // 然后打印在界面上
////        ui->label_2->setText(tr("(%1  %2  ||  %3  %4)").arg(x_pos).arg(y_pos).arg(x_val).arg(y_val));

//        QDateTime time_1= QDateTime::fromTime_t(x_val);
//        QString earn_xtime = time_1.toString("yyyy-MM-dd hh:mm:ss");
//        ui->label_2->setText(tr("(%1  %2)").arg(earn_xtime).arg(y_val));
//}

//IndicatorLight_3

//实时监控部分
void Contents::on_pushButton_clicked()
{
    ui->pushButton_5->show();
//    ui->comboBox->show();
    m_pTimer->start();
    historyinfo->setVisible(false);
    testpoint_info->setVisible(false);
    historycharts->setVisible(false);

    ui->tabWidget_3->show();
    //    ui->tabWidget_3->setTabText(0,"结构应变实时变化曲线图");
    //    ui->tabWidget_3->setTabText(1,"结构应变实时变化数据表");
    //    ui->IndicatorLight_3->clearMask();
    //    ui->IndicatorLight_3->clearFocus();



}

//历史数据部分
void Contents::on_pushButton_2_clicked()
{
    ui->pushButton_5->hide();
//    ui->comboBox->hide();
    m_pTimer->stop();
    ui->tabWidget_3->hide();
    historycharts->setVisible(true);

    //    ui->widget_3->graph(0)->data().data()->clear();//清除

    historyinfo->setVisible(false);
    testpoint_info->setVisible(false);






    //    ui->tabWidget_3->setTabText(0,"结构应变历史变化曲线图");
    //    ui->tabWidget_3->setTabText(1,"结构应变历史变化数据表");



    ui->widget_3->replot();//折线图--数据刷新
}

//告警设计部分
void Contents::on_pushButton_3_clicked()
{
    ui->pushButton_5->hide();
//    ui->comboBox->hide();
    historyinfo->setVisible(true);
    testpoint_info->setVisible(false);
    historycharts->setVisible(false);
    //    historyinfo->raise();

    ui->tabWidget_3->hide();

    connect(historyinfo,SIGNAL(GetUdpLogMsg()),this,SLOT(DisplayMsg()));
    //**************************************
    //设置告警表格;对异常进行判断，触发警报.



}

//设备信息部分
//void Contents::on_pushButton_4_clicked()
//{
//    ui->widget_11->hide();
//    ui->tabWidget_3->hide();
//    historycharts->setVisible(false);
////    historyinfo->close();
//    historyinfo->setVisible(false);
////    historyinfo->lower();

//    testpoint_info->setVisible(true);


//}



//void Contents::on_pushButton_6_clicked()//历史折线图筛选确认按钮
//{
//    //获取到线文本框内的内容
//    ui->dateTimeEdit_5->text();
//    ui->dateTimeEdit_6->text();
//    qDebug()<<"内容显示为："<<ui->dateTimeEdit_5->text();
//    qDebug()<<"内容显示为："<<ui->dateTimeEdit_6->text();

//    //提取起始日期信息

//    QString start_str = ui->dateTimeEdit_5->text();
//    QStringList start_list = start_str.split(" ");
//    QString start_year = start_list[0]; // "2000/1/1"
//    QString start_month = start_list[1]; // "0:00"

//    QString years_month_day=start_year;
//    QStringList test = years_month_day.split("/");
//    int year=test[0].toInt();
//    int month=test[1].toInt();
//    int day=test[2].toInt();

//     qDebug()<<"显示分割出的字符串为："<<start_str;
//     qDebug()<<"显示分割出的字符串为："<<start_year;
//     qDebug()<<"显示分割出的字符串为："<<start_month;

//     qDebug()<<"显示分割出的字符串为："<<year;
//     qDebug()<<"显示分割出的字符串为："<<month;
//     qDebug()<<"显示分割出的字符串为："<<day;



//    //提取结束日期信息
//    QString end_str = ui->dateTimeEdit_6->text();
//    QStringList end_list = end_str.split(" ");

//    QString end_year = end_list[0]; // "2000/1/1"
//    QString end_month = end_list[1]; // "0:00"

//    QString end_years_month_day=end_year;
//    QStringList test_end = end_years_month_day.split("/");
//    int EndYear=test_end[0].toInt();
//    int EndMonth=test_end[1].toInt();
//    int End_day=test_end[2].toInt();


//    qDebug()<<"显示分割出的字符串为："<<EndYear;
//    qDebug()<<"显示分割出的字符串为："<<EndMonth;
//    qDebug()<<"显示分割出的字符串为："<<End_day;


//    if(year>EndYear||(year<=EndYear && month>EndMonth)||(year<=EndYear && month<=EndMonth && day>End_day))//暂时只设置了日期部分（时间部分还需判断）
//    {
//           QMessageBox::warning(this, "warning", "初始时间不能大于结束时间！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//    }
//    else
//    {
//        //*****************************************
//        //填写筛选刷新后历史折线图数据部分





//        QMessageBox::information(this, "success！", "筛选成功！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//    }


//}

//void Contents::on_pushButton_5_clicked()//历史图表筛选确认按钮
//{
//    //获取到线文本框内的内容
//    ui->dateTimeEdit->text();
//    ui->dateTimeEdit_2->text();
//    qDebug()<<"内容显示为："<<ui->dateTimeEdit->text();
//    qDebug()<<"内容显示为："<<ui->dateTimeEdit_2->text();

//    //提取起始日期信息

//    QString start_str = ui->dateTimeEdit->text();
//    QStringList start_list = start_str.split(" ");
//    QString start_year = start_list[0]; // "2000/1/1"
//    QString start_month = start_list[1]; // "0:00"

//    QString years_month_day=start_year;
//    QStringList test = years_month_day.split("/");
//    int year=test[0].toInt();
//    int month=test[1].toInt();
//    int day=test[2].toInt();

//     qDebug()<<"显示分割出的字符串为："<<start_str;
//     qDebug()<<"显示分割出的字符串为："<<start_year;
//     qDebug()<<"显示分割出的字符串为："<<start_month;

//     qDebug()<<"显示分割出的字符串为："<<year;
//     qDebug()<<"显示分割出的字符串为："<<month;
//     qDebug()<<"显示分割出的字符串为："<<day;



//    //提取结束日期信息
//    QString end_str = ui->dateTimeEdit_2->text();
//    QStringList end_list = end_str.split(" ");

//    QString end_year = end_list[0]; // "2000/1/1"
//    QString end_month = end_list[1]; // "0:00"

//    QString end_years_month_day=end_year;
//    QStringList test_end = end_years_month_day.split("/");
//    int EndYear=test_end[0].toInt();
//    int EndMonth=test_end[1].toInt();
//    int End_day=test_end[2].toInt();


//    qDebug()<<"显示分割出的字符串为："<<EndYear;
//    qDebug()<<"显示分割出的字符串为："<<EndMonth;
//    qDebug()<<"显示分割出的字符串为："<<End_day;


//    if(year>EndYear||(year<=EndYear && month>EndMonth)||(year<=EndYear && month<=EndMonth && day>End_day))//暂时只设置了日期部分（时间部分还需判断）
//    {
//           QMessageBox::warning(this, "warning", "初始时间不能大于结束时间！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//    }
//    else
//    {
//        //**************************************
//        //填写筛选刷新后历史图表数据部分



//        QMessageBox::information(this, "success！", "筛选成功！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
//    }



//}

void Contents::on_pushButton_4_clicked()
{
    ui->pushButton_5->hide();
//    ui->comboBox->hide();
    m_pTimer->stop();
    ui->tabWidget_3->hide();
    historycharts->setVisible(false);

    //    ui->widget_3->graph(0)->data().data()->clear();//清除

    historyinfo->setVisible(false);
    testpoint_info->setVisible(true);



}
//******************************************************************************************************************************************************

void Contents::set_conten_homet(HomePage *pwidget)
{
    d = pwidget;

}

void Contents::on_pushButton_5_clicked()
{
    this->close();
    d->show();
}
