#include "historycharts.h"
#include "ui_historycharts.h"

QString info;
void HistoryCharts::send_Token_Data(QString Token_data)
{
    strToken=Token_data;
    //    qDebug()<<"historycharts传过来是：传过来的Token数据是："<<strToken;


}

HistoryCharts::HistoryCharts(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryCharts)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(0);//切换到第一个tab
    ui->comboBox->setView(new QListView());
    ui->tabWidget->tabBar()->close();

    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(select_click(int)));

    //初始化末尾时间
    QDateTime MyThetime1 = QDateTime::currentDateTime(); //获取当前时间

    ui->dateTimeEdit->setDateTime(QDateTime::fromString("2022-5-16 0:00", "yyyy-MM-dd hh:mm:ss"));
    ui->dateTimeEdit_2->setDateTime(MyThetime1);
    ui->dateTimeEdit_5->setDateTime(QDateTime::fromString("2022-5-16 0:00", "yyyy-MM-dd hh:mm:ss"));
    ui->dateTimeEdit_6->setDateTime(MyThetime1);

    //获取信息 http链接
    isLogin = false;
    //    ui->pushButton_2->setEnabled(false);
    httpLogin = new QNetworkAccessManager(this);
    projectCode = 1552;
    // 绑定请求完成信号和完成后的操作
    connect(httpLogin, SIGNAL(finished(QNetworkReply *)), this, SLOT(loginSuccess(QNetworkReply *)));

    this->str_all="";



    ui->tabWidget->setStyleSheet("QTabWidget:pane {border-top:0px solid #e8f3f9;background: transparent;}\
                                 QTabWidget#tabWidget{background-color:rgb(255,0,0);background:  transparent;}\
                                 QTabBar::tab{background-color:rgb(220,200,180);color:rgb(255,255,255);font:75 13pt '微软雅黑';background:  transparent;text-decoration: underline;}\
                                 QTabBar::tab::selected{background-color:rgb(0,100,200);color:rgb(255,255,255);font:75 14pt '微软雅黑';background:  transparent;text-decoration: underline;}");

                                 ui->widget_2->setObjectName("mainwidget");
            //    ui->widget_2->setStyleSheet("#mainwidget{border-image:url(:/back/image/mybackgroundimage.jpg)}");
            ui->widget_2->setAttribute(Qt::WA_TranslucentBackground);//设置子窗口为透明背景色


    QDateTime Thetime1 = QDateTime::currentDateTime(); //获取当前时间
    int cut_timestamp = Thetime1.toTime_t(); //将当前时间转为时间戳

//    init_paint(ui->widget_3,cut_timestamp,"东左测点","东右测点");
//    init_paint(ui->widget_4,cut_timestamp,"东左吊杆","东右吊杆");
//    init_paint(ui->widget_5,cut_timestamp,"西左测点","西右测点");
//    init_paint(ui->widget_6,cut_timestamp,"西左吊杆","西右吊杆");

    init_paint(ui->widget_3,cut_timestamp,"东1测点","南3测点");
    init_paint(ui->widget_4,cut_timestamp,"东2吊杆","南4吊杆");
    init_paint(ui->widget_5,cut_timestamp,"西5测点","北7测点");
    init_paint(ui->widget_6,cut_timestamp,"西6吊杆","北8吊杆");




}

HistoryCharts::~HistoryCharts()
{
    delete ui;
}


//实现选择下拉框槽函数
void HistoryCharts::select_click(int item)
{
    //    ui->comboBox->setCurrentIndex(item);
    qDebug()<<"点击触发到这里的信息";

    ui->comboBox->setCurrentIndex(item);
    ui->tabWidget->setCurrentIndex(item);

    //    if(ui->comboBox->currentText()=="挂篮东")
    //    {
    //        ui->tabWidget_3->setCurrentIndex(item);
    //    }
    //    if(ui->comboBox->currentText()=="挂篮西")
    //    {
    //        ui->tabWidget_3->setCurrentIndex(item);
    //    }

}

void HistoryCharts::receive_data(QString rec_datas)
{
    info=rec_datas;
}

//初始化图
void HistoryCharts::init_paint(QCustomPlot *widgets,double cut_timestamp1,const char * tab_name1,const char * tab_name2)
{


    //    QDateTime Thetime1 = QDateTime::currentDateTime(); //获取当前时间
    //    int cut_timestamp1 = Thetime1.toTime_t(); //将当前时间转为时间戳

    widgets->xAxis->grid()->setVisible(false);//去除横坐标网格线
    widgets->yAxis->grid()->setVisible(false);

    //QCPAxisTickerDateTime 时间坐标轴 必须要用智能指针
    QSharedPointer<QCPAxisTickerDateTime> timer1(new QCPAxisTickerDateTime);

    //设置时间格式
    timer1->setDateTimeFormat("MM-dd hh:mm");


    //设置时间轴 一共几格
    timer1->setTickCount(3);

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
    //     widgets->yAxis->setRange(0,300);

    widgets->addGraph();
    widgets->addGraph();

    widgets->graph(0)->setPen(QPen(Qt::green));
    widgets->graph(1)->setPen(QPen(Qt::red));
    widgets->graph(0)->setName(tr(tab_name1));
    widgets->graph(1)->setName(tr(tab_name2));

}

void HistoryCharts::on_pushButton_6_clicked()
{
    //获取到线文本框内的内容
    ui->dateTimeEdit->setDateTime(QDateTime::fromString(ui->dateTimeEdit_5->text(),"yyyy/MM/dd hh:mm:ss"));
    ui->dateTimeEdit_6->text();
    qDebug()<<"内容显示为："<<ui->dateTimeEdit_5->text();
    qDebug()<<"内容显示为："<<ui->dateTimeEdit_6->text();

    //提取起始日期信息

    QString start_str = ui->dateTimeEdit_5->text();
    QStringList start_list = start_str.split(" ");
    QString start_year = start_list[0]; // "2000/1/1"
    QString start_month = start_list[1]; // "0:00"

    QString years_month_day=start_year;
    QStringList test = years_month_day.split("/");
    int year=test[0].toInt();
    int month=test[1].toInt();
    int day=test[2].toInt();

    QString hour_m_s=start_month;
    QStringList spl_str = hour_m_s.split(":");
    int hour=spl_str[0].toInt();
    int min=spl_str[1].toInt();

//    qDebug()<<"显示分割出的字符串为："<<start_str;
//    qDebug()<<"显示分割出的字符串为："<<start_year;
//    qDebug()<<"显示分割出的字符串为："<<start_month;

//    qDebug()<<"显示分割出的字符串为："<<year;
//    qDebug()<<"显示分割出的字符串为："<<month;
//    qDebug()<<"显示分割出的字符串为："<<day;
//    qDebug()<<"显示分割出的字符串为："<<hour;
//    qDebug()<<"显示分割出的字符串为："<<min;

    str_all=test[0]+"-"+test[1]+"-"+test[2]+" "+spl_str[0]+":"+spl_str[1]+":00.000";
    short_str_all=test[0]+"-"+test[1]+"-"+test[2]+" "+spl_str[0]+":"+spl_str[1];
    qDebug()<<"显示Str分割出的字符串为："<<str_all;


    //提取结束日期信息
    QString end_str = ui->dateTimeEdit_6->text();
    QStringList end_list = end_str.split(" ");

    QString end_year = end_list[0]; // "2000/1/1"
    QString end_month = end_list[1]; // "0:00"

    QString end_years_month_day=end_year;
    QStringList test_end = end_years_month_day.split("/");
    int EndYear=test_end[0].toInt();
    int EndMonth=test_end[1].toInt();
    int End_day=test_end[2].toInt();

    QString End_hour_m_s=end_month;
    QStringList End_spl_str = End_hour_m_s.split(":");


    int End_hour=End_spl_str[0].toInt();
    int End_min=End_spl_str[1].toInt();


//    qDebug()<<"显示分割出的字符串为："<<EndYear;
//    qDebug()<<"显示分割出的字符串为："<<EndMonth;
//    qDebug()<<"显示分割出的字符串为："<<End_day;
//    qDebug()<<"显示分割出的字符串为："<<End_hour;
//    qDebug()<<"显示分割出的字符串为："<<End_min;

    End_str_all=test_end[0]+"-"+test_end[1]+"-"+test_end[2]+" "+End_spl_str[0]+":"+End_spl_str[1]+":00.000";
    short_End_str_all=test_end[0]+"-"+test_end[1]+"-"+test_end[2]+" "+End_spl_str[0]+":"+End_spl_str[1];
//    qDebug()<<"显示End分割出的字符串为："<<End_str_all;

    QDateTime start,end;
    end = QDateTime::fromString(ui->dateTimeEdit_6->text(),"yyyy/MM/dd hh:mm:ss");
    start = QDateTime::fromString(ui->dateTimeEdit_5->text(),"yyyy/MM/dd hh:mm:ss");

    unsigned int su=  QDateTime::fromString(ui->dateTimeEdit_6->text(),"yyyy/MM/dd hh:mm:ss").toTime_t();
    unsigned int ku=  QDateTime::fromString(ui->dateTimeEdit_5->text(),"yyyy/MM/dd hh:mm:ss").toTime_t();

//    int num_time=(su-ku)/60;//信息条数

//    int validLicenseDays = start.daysTo(end); //求时间差;
    long long validLicenseDays_sec = start.secsTo(end); //求时间差;

//    qDebug()<<"时间差为："<<validLicenseDays;




    if(year>EndYear||(year<=EndYear && month>EndMonth)||(year<=EndYear && month<=EndMonth && day>End_day))//暂时只设置了日期部分（时间部分还需判断）
    {
        QMessageBox::warning(this, "warning", "初始时间不能大于结束时间！", QMessageBox::Yes |QMessageBox::Yes);
    }
    //    else if(num_time>7200)
    else if(validLicenseDays_sec>5*24*60*60)
    {
        QMessageBox::warning(this, "warning", "查询最大区间为五天！", QMessageBox::Yes |QMessageBox::Yes);
    }
    else
    {
        //*****************************************
        //填写筛选刷新后历史折线图数据部分
        //实现数据接收请求
        //        qDebug()<<"historycharts传过来是："<<strToken;
        QString ffffff=info;
        QString sdkjf=info.toUtf8();

        qDebug()<<"Enter timeout processing function\n";
        //    ui->widget_3->graph(0)->data().data()->clear();//清除


        QUrl url("https://www.everiaction.com/IOT-ADAPTER-CUSTOM/es/point/getData");
        QUrlQuery query;
        query.addQueryItem("projectCode", QString::number(projectCode));//项目编号
        //    query.addQueryItem("pointCode", "test");//测点编号


        QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
        QString strtime = dateTime .toString("yyyy-MM-dd hh:mm");//格式化时间


        qDebug()<<"获取到的时间字符串为："<<ui->dateTimeEdit_5->text();
        //开始时间：str_all
        //结束时间：End_str_all
        query.addQueryItem("beginDate", str_all);//开始时间
        query.addQueryItem("endDate", End_str_all);//开始时间

        //            ui->dateTimeEdit_5->text();
        //            ui->dateTimeEdit_6->text();

//        double yg=QDateTime::fromString(ui->dateTimeEdit_5->text(), "yyyy/MM/dd hh:mm:ss").toTime_t();
//        double gf=QDateTime::fromString(ui->dateTimeEdit_6->text(), "yyyy-MM-dd hh:mm:ss").toTime_t();

        //        query.addQueryItem("beginDate", "2022-05-13 00:00:00.000");//开始时间
        //        query.addQueryItem("endDate", strtime);//结束时间
        query.addQueryItem("pageSize", "7200");//返回数据条数
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
        reqLogin.setRawHeader("Authorization",info.toUtf8());//Authorization身份验证
        //发送数据
        httpLogin->get(reqLogin);




        //        QMessageBox::information(this, "success！", "筛选成功！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }

}


//获取传递来的信息
int HistoryCharts::loginSuccess(QNetworkReply *reply)
{
    //    qDebug()<<"进入到该函数";
    update_data(reply);
    //    update_plot();
}

int HistoryCharts::update_data(QNetworkReply *reply)
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



                    qDebug()<<"进入到图形之后";
                    QJsonArray dataArr=data.toArray();

                    //                    qDebug()<<"收到的数据是："<<dataArr;

                    //******************************************************************/此处注释是测试数据下载为txt
                    // QJsonArray转换成QByteArray
                    //                       QJsonDocument document=QJsonDocument(dataArr);
                    //                       QByteArray byte_array = document.toJson();
                    //                       saveMyData(byte_array,"all_file");
                    //**********************************************************************

                    struct found_Info MySaves;
                    x1.clear();
                    y1.clear();
                    int sizes =dataArr.size();
                    for(int i=0;i<sizes;i++)
                    {
                        MySaves.pointCode=dataArr.at(i).toObject().value("pointCode").toString();
                        MySaves.pointName=dataArr.at(i).toObject().value("pointName").toString();
                        MySaves.factorName=dataArr.at(i).toObject().value("factorName").toString();
                        QJsonArray list_arr=dataArr.at(i).toObject().value("listPhys").toArray();
                        int size_list = list_arr.size();
                        //                        if(MySaves.pointName=="东左测点")
                        if(MySaves.pointName=="东1测点")
                        {
                            ui->widget_3->graph(0)->data().data()->clear();//清除

                            for(int j=0;j<size_list;j++)
                            {
                                MySaves.phy=list_arr.at(j).toObject().value("phy").toString();
                                if(MySaves.phy=="应变变化值")
                                {
                                    QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                    qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                    int my_num=sec_arr.size();

                                    for(int s=0;s<my_num;s++)
                                    {
                                        x1.push_back(QDateTime::fromString(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19), "yyyy-MM-dd hh:mm:ss").toTime_t());
                                        y1.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        //
                                    }
                                }


                            }

                            update_plot(ui->widget_3,x1,y1,0);
                            x1.clear();
                            y1.clear();
                        }

                        //                        if(MySaves.pointName=="东右测点")
                        if(MySaves.pointName=="东2吊杆")
                        {
                            ui->widget_4->graph(0)->data().data()->clear();//清除

                            for(int j=0;j<size_list;j++)
                            {
                                MySaves.phy=list_arr.at(j).toObject().value("phy").toString();
                                if(MySaves.phy=="应变变化值")
                                {
                                    QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                    qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                    int my_num=sec_arr.size();


                                    for(int s=0;s<my_num;s++)
                                    {
                                        x1.push_back(QDateTime::fromString(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19), "yyyy-MM-dd hh:mm:ss").toTime_t());
                                        y1.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        //
                                    }
                                }


                            }

                            update_plot(ui->widget_4,x1,y1,0);
                            x1.clear();
                            y1.clear();

                        }

                        //                        if(MySaves.pointName=="东左吊杆")
                        if(MySaves.pointName=="北7测点")
                        {
                            ui->widget_5->graph(1)->data().data()->clear();//清除

                            for(int j=0;j<size_list;j++)
                            {
                                MySaves.phy=list_arr.at(j).toObject().value("phy").toString();
                                if(MySaves.phy=="应变变化值")
                                {
                                    QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                    qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                    int my_num=sec_arr.size();


                                    for(int s=0;s<my_num;s++)
                                    {
                                        x1.push_back(QDateTime::fromString(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19), "yyyy-MM-dd hh:mm:ss").toTime_t());
                                        y1.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        //
                                    }
                                }


                            }

                            update_plot(ui->widget_5,x1,y1,1);
                            x1.clear();
                            y1.clear();
                        }

                        //                        if(MySaves.pointName=="东右吊杆")
                        if(MySaves.pointName=="北8吊杆")
                        {
                            ui->widget_6->graph(1)->data().data()->clear();//清除

                            for(int j=0;j<size_list;j++)
                            {
                                MySaves.phy=list_arr.at(j).toObject().value("phy").toString();
                                if(MySaves.phy=="应变变化值")
                                {
                                    QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                    qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                    int my_num=sec_arr.size();


                                    for(int s=0;s<my_num;s++)
                                    {
                                        x1.push_back(QDateTime::fromString(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19), "yyyy-MM-dd hh:mm:ss").toTime_t());
                                        y1.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        //
                                    }
                                }


                            }

                            update_plot(ui->widget_6,x1,y1,1);
                            x1.clear();
                            y1.clear();

                        }

                        //数据异常 未接受到应变变化值
                        //                        if(MySaves.pointName=="西左测点")
                        if(MySaves.pointName=="南3测点")
                        {
                            ui->widget_3->graph(1)->data().data()->clear();//清除

                            for(int j=0;j<size_list;j++)
                            {
                                MySaves.phy=list_arr.at(j).toObject().value("phy").toString();
                                if(MySaves.phy=="应变变化值")
                                {
                                    QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                    qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                    int my_num=sec_arr.size();


                                    for(int s=0;s<my_num;s++)
                                    {
                                        x1.push_back(QDateTime::fromString(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19), "yyyy-MM-dd hh:mm:ss").toTime_t());
                                        y1.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        //
                                    }
                                }


                            }

                            update_plot(ui->widget_3,x1,y1,1);
                            x1.clear();
                            y1.clear();
                        }



                        //                        if(MySaves.pointName=="西右测点")
                        if(MySaves.pointName=="南4吊杆")
                        {
                            ui->widget_4->graph(1)->data().data()->clear();//清除

                            for(int j=0;j<size_list;j++)
                            {
                                MySaves.phy=list_arr.at(j).toObject().value("phy").toString();
                                if(MySaves.phy=="应变变化值")
                                {
                                    QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                    qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                    int my_num=sec_arr.size();


                                    for(int s=0;s<my_num;s++)
                                    {
                                        x1.push_back(QDateTime::fromString(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19), "yyyy-MM-dd hh:mm:ss").toTime_t());
                                        y1.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        //
                                    }
                                }


                            }

                            update_plot(ui->widget_4,x1,y1,1);
                            x1.clear();
                            y1.clear();
                        }

                        //数据异常 未接受到应变变化值
                        //                        if(MySaves.pointName=="西左吊杆")
                        if(MySaves.pointName=="西5测点")
                        {
                            ui->widget_5->graph(0)->data().data()->clear();//清除

                            for(int j=0;j<size_list;j++)
                            {
                                MySaves.phy=list_arr.at(j).toObject().value("phy").toString();
                                if(MySaves.phy=="应变变化值")
                                {
                                    QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                    qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                    int my_num=sec_arr.size();


                                    for(int s=0;s<my_num;s++)
                                    {


                                        x1.push_back(QDateTime::fromString(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19), "yyyy-MM-dd hh:mm:ss").toTime_t());
                                        y1.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        //

                                    }
                                }


                            }

                            update_plot(ui->widget_5,x1,y1,0);
                            x1.clear();
                            y1.clear();
                        }




                        //                        if(MySaves.pointName=="西右吊杆")
                        if(MySaves.pointName=="西6吊杆")
                        {
                            ui->widget_6->graph(0)->data().data()->clear();//清除

                            for(int j=0;j<size_list;j++)
                            {
                                MySaves.phy=list_arr.at(j).toObject().value("phy").toString();
                                if(MySaves.phy=="应变变化值")
                                {
                                    QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                    qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                    int my_num=sec_arr.size();


                                    for(int s=0;s<my_num;s++)
                                    {
                                        x1.push_back(QDateTime::fromString(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19), "yyyy-MM-dd hh:mm:ss").toTime_t());
                                        y1.push_back(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        //
                                    }
                                }


                            }

                            update_plot(ui->widget_6,x1,y1,0);
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





void HistoryCharts::update_plot(QCustomPlot *select_Widget,QVector<double> x1, QVector<double> y1,int dex)
{


    //    select_Widget->graph(1)->data().data()->clear();//清除
    QDateTime::fromString(short_str_all, "yyyy-MM-dd hh:mm:ss").toTime_t();
    QDateTime::fromString(short_End_str_all, "yyyy-MM-dd hh:mm:ss").toTime_t();

    QString ccccc=short_str_all;
    QString sdfffffff=short_End_str_all;

    //轴当前可见部分的范围
    //    QDateTime Thetime1 = QDateTime::currentDateTime(); //获取当前时间
    //    double cut_timestamp1 = Thetime1.toTime_t(); //将当前时间转为时间戳
    //    select_Widget->xAxis->setRange(x1[0]-600,x1[0]+600);
    //    select_Widget->yAxis->setRange(-1,150);
    //    select_Widget->xAxis->setRange(QDateTime::fromString(short_str_all, "yyyy-MM-dd hh:mm:ss").toTime_t(),QDateTime::fromString(short_End_str_all, "yyyy-MM-dd hh:mm:ss").toTime_t());
    //    select_Widget->yAxis->setRange(0,1000);

    QVector<double> tempx,tempy;
    tempx.clear();
    tempy.clear();
    tempx = x1;
    tempy = y1;

    //    for (int i = 0; i < 500; i++) {
    //        tempx.push_back(i);
    //        tempy.push_back(i+1);
    //    }
    if (tempy.isEmpty())
    {
        return;
    }

    if (tempx.isEmpty())
    {
        return;
    }

//    double sta_time = x1[0];
    QDateTime::fromString(short_str_all, "yyyy-MM-dd hh:mm:ss").toTime_t();
//    double end_time = QDateTime::fromString(short_End_str_all, "yyyy-MM-dd hh:mm:ss").toTime_t();
    select_Widget->xAxis->setRange(QDateTime::fromString(ui->dateTimeEdit_5->text(),"yyyy/MM/dd hh:mm:ss").toTime_t(),QDateTime::fromString(ui->dateTimeEdit_6->text(),"yyyy/MM/dd hh:mm:ss").toTime_t());
    //    select_Widget->xAxis->setRange(x1[0],x1[0]+30000);
    select_Widget->yAxis->setRange(y1[0]-100,y1[0]+100);



    select_Widget->graph(dex)->addData(tempx,tempy);
    //    select_Widget->graph(1)->addData(x2,y2);
    select_Widget->replot();



}

void HistoryCharts::on_pushButton_5_clicked()
{
    str_all="";
    short_str_all="";
    End_str_all="";
    short_End_str_all="";

    ui->dateTimeEdit_5->setDateTime(QDateTime::fromString(ui->dateTimeEdit->text(),"yyyy/MM/dd hh:mm:ss"));

    //获取到线文本框内的内容
    ui->dateTimeEdit->text();
    ui->dateTimeEdit_2->text();
    qDebug()<<"内容显示为："<<ui->dateTimeEdit->text();
    qDebug()<<"内容显示为："<<ui->dateTimeEdit_2->text();

    //提取起始日期信息

    QString start_str = ui->dateTimeEdit->text();
    QStringList start_list = start_str.split(" ");
    QString start_year = start_list[0]; // "2000/1/1"
    QString start_month = start_list[1]; // "0:00"

    QString years_month_day=start_year;
    QStringList test = years_month_day.split("/");
    int year=test[0].toInt();
    int month=test[1].toInt();
    int day=test[2].toInt();

    QString hour_m_s=start_month;
    QStringList spl_str = hour_m_s.split(":");
    int hour=spl_str[0].toInt();
    int min=spl_str[1].toInt();

    qDebug()<<"显示分割出的字符串为："<<start_str;
    qDebug()<<"显示分割出的字符串为："<<start_year;
    qDebug()<<"显示分割出的字符串为："<<start_month;

    qDebug()<<"显示分割出的字符串为："<<year;
    qDebug()<<"显示分割出的字符串为："<<month;
    qDebug()<<"显示分割出的字符串为："<<day;
    qDebug()<<"显示分割出的字符串为："<<hour;
    qDebug()<<"显示分割出的字符串为："<<min;

    str_all=test[0]+"-"+test[1]+"-"+test[2]+" "+spl_str[0]+":"+spl_str[1]+":00.000";
    short_str_all=test[0]+"-"+test[1]+"-"+test[2]+" "+spl_str[0]+":"+spl_str[1];
    qDebug()<<"显示Str分割出的字符串为："<<str_all;


    //提取结束日期信息
    QString end_str = ui->dateTimeEdit_2->text();
    QStringList end_list = end_str.split(" ");

    QString end_year = end_list[0]; // "2000/1/1"
    QString end_month = end_list[1]; // "0:00"

    QString end_years_month_day=end_year;
    QStringList test_end = end_years_month_day.split("/");
    int EndYear=test_end[0].toInt();
    int EndMonth=test_end[1].toInt();
    int End_day=test_end[2].toInt();

    QString End_hour_m_s=end_month;
    QStringList End_spl_str = End_hour_m_s.split(":");


    int End_hour=End_spl_str[0].toInt();
    int End_min=End_spl_str[1].toInt();


    qDebug()<<"显示分割出的字符串为："<<EndYear;
    qDebug()<<"显示分割出的字符串为："<<EndMonth;
    qDebug()<<"显示分割出的字符串为："<<End_day;
    qDebug()<<"显示分割出的字符串为："<<End_hour;
    qDebug()<<"显示分割出的字符串为："<<End_min;
    End_str_all=test_end[0]+"-"+test_end[1]+"-"+test_end[2]+" "+End_spl_str[0]+":"+End_spl_str[1]+":00.000";
    short_End_str_all=test_end[0]+"-"+test_end[1]+"-"+test_end[2]+" "+End_spl_str[0]+":"+End_spl_str[1];
    qDebug()<<"显示End分割出的字符串为："<<End_str_all;

    unsigned int su=  QDateTime::fromString(ui->dateTimeEdit_6->text(),"yyyy/MM/dd hh:mm:ss").toTime_t();
    unsigned int ku=  QDateTime::fromString(ui->dateTimeEdit_5->text(),"yyyy/MM/dd hh:mm:ss").toTime_t();

    unsigned int num_time=(su-ku)/60;//信息条数


    if(year>EndYear||(year<=EndYear && month>EndMonth)||(year<=EndYear && month<=EndMonth && day>End_day))//暂时只设置了日期部分（时间部分还需判断）
    {
        QMessageBox::warning(this, "warning", "初始时间不能大于结束时间！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    else if(num_time>7200)
    {
        QMessageBox::warning(this, "warning", "只能查询五天内数据！", QMessageBox::Yes |  QMessageBox::Yes);

    }
    else
    {
        //*****************************************
        //填写筛选刷新后历史折线图数据部分
        //实现数据接收请求
        //        qDebug()<<"historycharts传过来是："<<strToken;
//        QString ffffff=info;
//        QString sdkjf=info.toUtf8();

        qDebug()<<"Enter timeout processing function\n";
        //    ui->widget_3->graph(0)->data().data()->clear();//清除


        QUrl url("https://www.everiaction.com/IOT-ADAPTER-CUSTOM/es/point/getData");
        QUrlQuery query;
        query.addQueryItem("projectCode", QString::number(projectCode));//项目编号
        //    query.addQueryItem("pointCode", "test");//测点编号


        QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
        QString strtime = dateTime .toString("yyyy-MM-dd hh:mm");//格式化时间


        qDebug()<<"获取到的时间字符串为："<<ui->dateTimeEdit_5->text();
        //开始时间：str_all
        //结束时间：End_str_all
        query.addQueryItem("beginDate", str_all);//开始时间
        query.addQueryItem("endDate", End_str_all);//开始时间

        //            ui->dateTimeEdit_5->text();
        //            ui->dateTimeEdit_6->text();

//        double yg=QDateTime::fromString(ui->dateTimeEdit->text(), "yyyy/MM/dd hh:mm:ss").toTime_t();
//        double gf=QDateTime::fromString(ui->dateTimeEdit_2->text(), "yyyy-MM-dd hh:mm:ss").toTime_t();

        //        query.addQueryItem("beginDate", "2022-05-13 00:00:00.000");//开始时间
        //        query.addQueryItem("endDate", strtime);//结束时间
        query.addQueryItem("pageSize", "7200");//返回数据条数
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
        reqLogin.setRawHeader("Authorization",info.toUtf8());//Authorization身份验证
        //发送数据
        httpLogin->get(reqLogin);




        //        QMessageBox::information(this, "success！", "筛选成功！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}


//东左
void HistoryCharts::on_pushButton_3_clicked()
{
    ui->widget_5->graph(0)->setVisible(true);
    ui->widget_6->graph(0)->setVisible(true);
    ui->widget_5->replot();
    ui->widget_6->replot();
}

void HistoryCharts::on_pushButton_4_clicked()
{
    //    ui->widget_3->graph(1)->hide();
    ui->widget_5->graph(0)->setVisible(false);//隐藏曲线
    //    graph(1)->setVisible(true);//显示曲线

    ui->widget_6->graph(0)->setVisible(false);//隐藏曲线
    ui->widget_6->replot();
    ui->widget_5->replot();

}
//东右
void HistoryCharts::on_pushButton_clicked()
{
    ui->widget_3->graph(0)->setVisible(true);
    ui->widget_4->graph(0)->setVisible(true);
    ui->widget_3->replot();
    ui->widget_4->replot();
}

void HistoryCharts::on_pushButton_2_clicked()
{
    ui->widget_3->graph(0)->setVisible(false);//隐藏曲线
    ui->widget_4->graph(0)->setVisible(false);//隐藏曲线
    ui->widget_4->replot();
    ui->widget_3->replot();
}

//西左显示
void HistoryCharts::on_pushButton_7_clicked()
{
    ui->widget_3->graph(1)->setVisible(true);
    ui->widget_4->graph(1)->setVisible(true);
    ui->widget_3->replot();
    ui->widget_4->replot();
}
//西左隐藏
void HistoryCharts::on_pushButton_9_clicked()
{
    ui->widget_3->graph(1)->setVisible(false);
    ui->widget_4->graph(1)->setVisible(false);
    ui->widget_3->replot();
    ui->widget_4->replot();
}

//西右显示
void HistoryCharts::on_pushButton_8_clicked()
{
    ui->widget_5->graph(1)->setVisible(true);
    ui->widget_6->graph(1)->setVisible(true);
    ui->widget_5->replot();
    ui->widget_6->replot();
}
//西右隐藏
void HistoryCharts::on_pushButton_10_clicked()
{
    ui->widget_5->graph(1)->setVisible(false);
    ui->widget_6->graph(1)->setVisible(false);
    ui->widget_5->replot();
    ui->widget_6->replot();
}


//测试使用保存txt文件函数
void HistoryCharts::saveMyData(QByteArray Mydata,QString Myname){
    //保存为TXT文件
    bool exist;
    QString fileName;

    QDir *folder = new QDir;
    exist = folder->exists("C:/Users/Administrator/Desktop/file_save");//查看目录是否存在（例子是保存到桌面）

    if(!exist){//不存在就创建
        bool ok = folder->mkdir("C:/Users/Administrator/Desktop/file_save");
        if(ok){
            QMessageBox::warning(this,tr("创建目录"),tr("创建成功!"));//添加提示方便查看是否成功创建
        }else{
            QMessageBox::warning(this,tr("创建目录"),tr("创建失败"));
        }
    }
    fileName = tr("C:/Users/Administrator/Desktop/file_save/%1.txt").arg(Myname);

    QFile f(fileName);
    if(!f.open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)){//追加写入 添加结束符\r\n
        QMessageBox::warning(this,tr("错误"),tr("打开文件失败,数据保存失败"));
        return ;
    }else{
        f.write(Mydata);
    }
    f.close();
}
