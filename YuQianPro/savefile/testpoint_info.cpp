#include "testpoint_info.h"
#include "ui_testpoint_info.h"
#include <QHeaderView>
#include <QDebug>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QtMath>
#include <math.h>

QString strToken_down;
void TestPoint_Info::down_receive_Data(QString data)
{
    //    strToken_down=data;
    qDebug()<<"传过来的数据是：2"<<strToken_down;
}


TestPoint_Info::TestPoint_Info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TestPoint_Info)
{
    ui->setupUi(this);

    //获取信息 http链接
    isLogin = false;
    //    ui->pushButton_2->setEnabled(false);
    httpLogin = new QNetworkAccessManager(this);
    projectCode = 1552;
    // 绑定请求完成信号和完成后的操作
    connect(httpLogin, SIGNAL(finished(QNetworkReply *)), this, SLOT(loginSuccess(QNetworkReply *)));

    //    ui->dateTimeEdit->setAttribute(Qt::WA_TranslucentBackground);
    //    ui->dateTimeEdit_2->setAttribute(Qt::WA_TranslucentBackground);

    ui->dateTimeEdit->setStyleSheet("QDateTimeEdit{background-color:transparent}"
                                    "QDateTimeEdit{border-width:0;border-style:outset}"
                                    "QDateTimeEdit{font: 75 26pt '微软雅黑'}"
                                    "QDateTimeEdit{text-decoration: underline}"
                                    "QDateTimeEdit{color: rgb(255, 255, 255)}"
                                    "QDateTimeEdit{border-width:0;border-style:outset}"
                                    );

    ui->dateTimeEdit_2->setStyleSheet("QDateTimeEdit{background-color:transparent}"
                                      "QDateTimeEdit{border-width:0;border-style:outset}"
                                      "QDateTimeEdit{font: 75 26pt '微软雅黑'}"
                                      "QDateTimeEdit{text-decoration: underline}"
                                      "QDateTimeEdit{color: rgb(255, 255, 255)}"
                                      "QDateTimeEdit{border-width:0;border-style:outset}"
                                      );


    //    ui->pushButton_5->setEnabled(false);


    //    ui->tableWidget->setRowCount(8);
    //    ui->tableWidget->setColumnCount(7);
    //    ui->tableWidget->setWindowTitle("QTableWidget & Item");
    //    ui->tableWidget->resize(1100, 500);  //设置表格
    ////    ui->widget->resize(18000,800);
    //    /*设置tablewidget等宽*/
    //    QHeaderView* headerView = ui->tableWidget->horizontalHeader();
    //    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    //    headerView->setSectionResizeMode(QHeaderView::Stretch);
    //    /*或者下面的代码*/
    //    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //    QStringList header;
    //    header<<"测点编号"<<"测点名称"<<"检测因素名称"<<"测点位置"<<"设备型号"<<"设备名称"<<"通道号";   //表头
    //    ui->tableWidget->setHorizontalHeaderLabels(header);
    //    ui->tableWidget->setItem(0,0,new QTableWidgetItem("东右吊杆"));
    //    ui->tableWidget->setItem(1,0,new QTableWidgetItem("东右测点"));
    //    ui->tableWidget->setItem(2,0,new QTableWidgetItem("东左吊杆"));
    //    ui->tableWidget->setItem(3,0,new QTableWidgetItem("东左测点"));
    //    ui->tableWidget->setItem(4,0,new QTableWidgetItem("西右测点"));
    //    ui->tableWidget->setItem(5,0,new QTableWidgetItem("西左吊杆"));
    //    ui->tableWidget->setItem(6,0,new QTableWidgetItem("西左吊杆2"));
    //    ui->tableWidget->setItem(7,0,new QTableWidgetItem("西左测点"));

    //    ui->tableWidget->setItem(0,1,new QTableWidgetItem("35"));


    //填充表格数据
    //    for(int i=0;i<7;i++)
    //    {
    //       QString datas[i]=data[i].pointCode;
    //       QString datas1[i]=data[i].pointName;
    //       QString datas2[i]=data[i].factorName;
    //       QString datas7[i]=data[i].position;
    //       QString datas3[i]=data[i].manuId;
    //       QString datas4[i]=data[i].deviceCode;
    //       QString datas5[i]=data[i].channelCode;

    //    }

    //把存储的数组数据放入表格
    //        for(int j=0;j<7;j++)
    //        {
    //            ui->tableWidget->setItem(j,1,new QTableWidgetItem(datas[j]));
    //            ui->tableWidget->setItem(j,3,new QTableWidgetItem(datas1[j]));
    //            ui->tableWidget->setItem(j,3,new QTableWidgetItem(datas2[j]));
    //            ui->tableWidget->setItem(j,4,new QTableWidgetItem(datas3[j]));
    //            ui->tableWidget->setItem(j,5,new QTableWidgetItem(datas4[j]));
    //            ui->tableWidget->setItem(j,6,new QTableWidgetItem(datas5[j]));
    //            ui->tableWidget->setItem(j,7,new QTableWidgetItem(datas6[j]));



    //        }


}

TestPoint_Info::~TestPoint_Info()
{
    delete ui;
}

void TestPoint_Info::receive_data_down(QString rec_datas)
{
    strToken_down=rec_datas;
    //     QString lll=info;
    //    qDebug()<<"mmmmmmmmmmmmmmmm";
}


void TestPoint_Info::on_pushButton_5_clicked()//下载按钮
{

    ui->pushButton_5->setEnabled(false);

    //获取到线文本框内的内容
    ui->dateTimeEdit->setDateTime(QDateTime::fromString(ui->dateTimeEdit->text(),"yyyy/MM/dd hh:mm:ss"));
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

    QDateTime start,end;
    end = QDateTime::fromString(ui->dateTimeEdit_2->text(),"yyyy/MM/dd hh:mm:ss");
    start = QDateTime::fromString(ui->dateTimeEdit->text(),"yyyy/MM/dd hh:mm:ss");

    int su=  QDateTime::fromString(ui->dateTimeEdit_2->text(),"yyyy/MM/dd hh:mm:ss").toTime_t();
    int ku=  QDateTime::fromString(ui->dateTimeEdit->text(),"yyyy/MM/dd hh:mm:ss").toTime_t();

    int num_time=(su-ku)/60;//信息条数

    int validLicenseDays = start.daysTo(end); //求时间差;
    int validLicenseDays_sec = start.secsTo(end); //求时间差;

    qDebug()<<"时间差为："<<validLicenseDays;
    //        if(days > validLicenseDays){
    //            validLicenseDays = days - validLicenseDays;
    //            return true;
    //        }else{
    //            validLicenseDays = 0;
    //            return false;
    //        }




    if(year>EndYear||(year<=EndYear && month>EndMonth)||(year<=EndYear && month<=EndMonth && day>End_day))//暂时只设置了日期部分（时间部分还需判断）
    {
        QMessageBox::warning(this, "warning", "初始时间不能大于结束时间！", QMessageBox::Yes |QMessageBox::Yes);
        ui->pushButton_5->setEnabled(true);
    }
    else if(validLicenseDays_sec==0)
    {
        QMessageBox::warning(this, "warning", "查询时间输入有误！", QMessageBox::Yes |QMessageBox::Yes);
        ui->pushButton_5->setEnabled(true);
    }
    //    else if(num_time>7200)
    else if(validLicenseDays_sec>5*24*60*60)
    {
        QMessageBox::warning(this, "warning", "查询最大区间为五天！", QMessageBox::Yes |QMessageBox::Yes);
        ui->pushButton_5->setEnabled(true);
//        double temp = validLicenseDays_sec/(60*60*24*5);
////        floor(temp);
//        //获取需要请求的次数  data为需要处理的数据 向下取整：floor(data) 或者 QFloor(data)  取余：validLicenseDays_sec%(60*60*24)
//        for(int numice=0;numice<floor(temp);numice++)
//        {
//            int numsdd=test[2].toInt()+(numice)*5;
//            QString jin=QString::number(numice);
//            str_all=test[0]+"-"+test[1]+"-"+jin+" "+spl_str[0]+":"+spl_str[1]+":00.000";//开始天数

//            int numsdd_end=test[2].toInt()+(1+numice)*5;
//            QString jin_end=QString::number(numsdd_end);
//            End_str_all=test[0]+"-"+test[1]+"-"+jin_end+" "+spl_str[0]+":"+spl_str[1]+":00.000";//开始天数


//            //***********************************************************************************
//            //填写筛选刷新后历史折线图数据部分
//            //实现数据接收请求

//            QUrl url("https://www.everiaction.com/IOT-ADAPTER-CUSTOM/es/point/getData");
//            QUrlQuery query;
//            query.addQueryItem("projectCode", QString::number(projectCode));//项目编号
//            //    query.addQueryItem("pointCode", "test");//测点编号

//            query.addQueryItem("beginDate", str_all);//开始时间
//            query.addQueryItem("endDate", End_str_all);//结束时间

//            query.addQueryItem("pageSize", "7200");//返回数据条数
//            //    query.addQueryItem("pageSize", "test");//排序方式
//            url.setQuery(query.query());//

//            // https需要的配置
//            QNetworkRequest reqLogin;
//            QSslConfiguration sslConf = reqLogin.sslConfiguration();
//            sslConf.setPeerVerifyMode(QSslSocket::VerifyNone);
//            sslConf.setProtocol(QSsl::TlsV1SslV3);
//            reqLogin.setSslConfiguration(sslConf);
//            //指定url
//            reqLogin.setUrl(url);
//            // 设置header
//            //.toUtf8()
//            reqLogin.setRawHeader("Authorization",strToken_down.toUtf8());//Authorization身份验证
//            //发送数据
//            httpLogin->get(reqLogin);

//        }

//        int sd = validLicenseDays_sec%(60*60*24*5);

//        int data_end=test[2].toInt()+(1+floor(temp))*5+floor(sd/60*60*24);
//        QString end_jin_end=QString::number(data_end);

//        int data_hour=spl_str[0].toInt()+floor(((sd%(60*60*24))*24*60*60)/(60*60));
//        int data_min=spl_str[1].toInt()+(sd%(60*60*24)*24*60*60)%(60*60)*60;
////        int data_mec

//        QString out_data=End_str_all;
//        QString out_data_end=test[0]+"-"+test[1]+"-"+end_jin_end+" "+spl_str[0]+":"+spl_str[1]+":00.000";//开始天数;

//       floor(sd/60*60*24)剩余五天内的天数
//       sd%(60*60*24)剩余最后不到一天的天数（小时数和分钟数和秒数 转换为的秒数）
//       (sd%(60*60*24))*24*60*60//剩余最后不到一天的剩余秒数
//       floor(((sd%(60*60*24))*24*60*60)/(60*60)); //小时
//       (sd%(60*60*24)*24*60*60)%(60*60))*60;//剩下的不到一小时的 小时数（分钟）
         //分钟再转换为秒数
//       (((sd%(60*60*24)*24*60*60)%(60*60))*60*60)%60)*60 //得到最后剩余的秒数
    }
    else
    {
        //*****************************************
        //填写筛选刷新后历史折线图数据部分
        //实现数据接收请求
        //   qDebug()<<"historycharts传过来是："<<strToken;
        QString ffffff=strToken_down;
        QString sdkjf=strToken_down.toUtf8();

        qDebug()<<"Enter timeout processing function\n";
        //    ui->widget_3->graph(0)->data().data()->clear();//清除


        QUrl url("https://www.everiaction.com/IOT-ADAPTER-CUSTOM/es/point/getData");
        QUrlQuery query;
        query.addQueryItem("projectCode", QString::number(projectCode));//项目编号
        //    query.addQueryItem("pointCode", "test");//测点编号


        QDateTime dateTime= QDateTime::currentDateTime();//获取系统当前的时间
        QString strtime = dateTime .toString("yyyy-MM-dd hh:mm");//格式化时间


        qDebug()<<"获取到的时间字符串为："<<ui->dateTimeEdit->text();
        //开始时间：str_all
        //结束时间：End_str_all
        query.addQueryItem("beginDate", str_all);//开始时间
        query.addQueryItem("endDate", End_str_all);//结束时间

        //            ui->dateTimeEdit->text();
        //            ui->dateTimeEdit_2->text();

        double yg=QDateTime::fromString(ui->dateTimeEdit->text(), "yyyy/MM/dd hh:mm:ss").toTime_t();
        double gf=QDateTime::fromString(ui->dateTimeEdit_2->text(), "yyyy-MM-dd hh:mm:ss").toTime_t();

        //        query.addQueryItem("beginDate", "2022-05-13 00:00:00.000");//开始时间
        //        query.addQueryItem("endDate", strtime);//结束时间
        query.addQueryItem("pageSize", "7200");//返回数据条数
        //    query.addQueryItem("pageSize", "test");//排序方式
        url.setQuery(query.query());

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
        reqLogin.setRawHeader("Authorization",strToken_down.toUtf8());//Authorization身份验证
        //发送数据
        httpLogin->get(reqLogin);

        //        QMessageBox::information(this, "success！", "筛选成功！",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}


int TestPoint_Info::loginSuccess(QNetworkReply *reply)
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
                    strToken_down = checkToken.toString();
                    qDebug() << "token:" << strToken_down;
                    qDebug() << "projectCode:" << projectCode;
                    qDebug() << "Login success !!!";
                    if (!strToken_down.isEmpty())
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
                    //设置一个下载数据总和用于写excel表

                    //                    int nub = 0;//变化值部分
                    //                    int nub1 = 0;//温度
                    //获取保存路径
                    QString filepath=QFileDialog::getSaveFileName(this,tr("Save"),".",tr(" (*.xlsx)"));
                    if(!filepath.isEmpty()){
                        ui->pushButton_5->setText("下载中...");
                        QAxObject *excel = new QAxObject(this);
                        //连接Excel控件
                        excel->setControl("Excel.Application");
                        //不显示窗体
                        excel->dynamicCall("SetVisible (bool Visible)","false");
                        //不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
                        excel->setProperty("DisplayAlerts", false);
                        //获取工作簿集合
                        QAxObject *workbooks = excel->querySubObject("WorkBooks");
                        //新建一个工作簿
                        workbooks->dynamicCall("Add");
                        //获取当前工作簿
                        QAxObject *workbook = excel->querySubObject("ActiveWorkBook");
                        //获取工作表集合
                        QAxObject *worksheets = workbook->querySubObject("Sheets");
                        //获取工作表集合的工作表1，即sheet1
                        QAxObject *worksheet = worksheets->querySubObject("Item(int)",1);

                        QAxObject *cellA,*cellB,*cellC,*cellD,*cellE,*cellF,*cellG,*cellH,*cellI,*cellJ,*cellK,*cellL,*cellM,*cellN,*cellO,*cellP,*cellQ,*cellR,*cellS,*cellT,*cellU,*cellV,*cellW,*cellX,*cellY,*cellZ,*cellAA,*cellAB,*cellAC,*cellAD,*cellAE,*cellAF;
                        //设置标题
                        int cellrow=1;
                        int cellrow1=1;
                        int cellrow2=1;
                        int cellrow3=1;
                        int cellrow4=1;
                        int cellrow5=1;
                        int cellrow6=1;
                        int cellrow7=1;

                        //设置要操作的单元格，如A1
                        QString A="A"+QString::number(cellrow);
                        QString B="B"+QString::number(cellrow);
                        QString C="C"+QString::number(cellrow);
                        QString D="D"+QString::number(cellrow);

                        QString E="E"+QString::number(cellrow1);
                        QString F="F"+QString::number(cellrow1);
                        QString G="G"+QString::number(cellrow1);
                        QString H="H"+QString::number(cellrow1);

                        QString I="I"+QString::number(cellrow2);
                        QString J="J"+QString::number(cellrow2);
                        QString K="K"+QString::number(cellrow2);
                        QString L="L"+QString::number(cellrow2);

                        QString M="M"+QString::number(cellrow3);
                        QString N="N"+QString::number(cellrow3);
                        QString O="O"+QString::number(cellrow3);
                        QString P="P"+QString::number(cellrow3);

                        QString Q="Q"+QString::number(cellrow4);
                        QString R="R"+QString::number(cellrow4);
                        QString S="S"+QString::number(cellrow4);
                        QString T="T"+QString::number(cellrow4);

                        QString U="U"+QString::number(cellrow5);
                        QString V="V"+QString::number(cellrow5);
                        QString W="W"+QString::number(cellrow5);
                        QString X="X"+QString::number(cellrow5);

                        QString Y="Y"+QString::number(cellrow6);
                        QString Z="Z"+QString::number(cellrow6);
                        QString AA="AA"+QString::number(cellrow6);
                        QString AB="AB"+QString::number(cellrow6);

                        QString AC="AC"+QString::number(cellrow7);
                        QString AD="AD"+QString::number(cellrow7);
                        QString AE="AE"+QString::number(cellrow7);
                        QString AF="AF"+QString::number(cellrow7);
                        //获取单元格
                        cellA = worksheet->querySubObject("Range(QVariant, QVariant)",A);
                        cellB = worksheet->querySubObject("Range(QVariant, QVariant)",B);
                        cellC = worksheet->querySubObject("Range(QVariant, QVariant)",C);
                        cellD = worksheet->querySubObject("Range(QVariant, QVariant)",D);

                        cellE = worksheet->querySubObject("Range(QVariant, QVariant)",E);
                        cellF = worksheet->querySubObject("Range(QVariant, QVariant)",F);
                        cellG = worksheet->querySubObject("Range(QVariant, QVariant)",G);
                        cellH = worksheet->querySubObject("Range(QVariant, QVariant)",H);

                        cellI = worksheet->querySubObject("Range(QVariant, QVariant)",I);
                        cellJ = worksheet->querySubObject("Range(QVariant, QVariant)",J);
                        cellK = worksheet->querySubObject("Range(QVariant, QVariant)",K);
                        cellL = worksheet->querySubObject("Range(QVariant, QVariant)",L);

                        cellM = worksheet->querySubObject("Range(QVariant, QVariant)",M);
                        cellN = worksheet->querySubObject("Range(QVariant, QVariant)",N);
                        cellO = worksheet->querySubObject("Range(QVariant, QVariant)",O);
                        cellP = worksheet->querySubObject("Range(QVariant, QVariant)",P);

                        cellQ = worksheet->querySubObject("Range(QVariant, QVariant)",Q);
                        cellR = worksheet->querySubObject("Range(QVariant, QVariant)",R);
                        cellS = worksheet->querySubObject("Range(QVariant, QVariant)",S);
                        cellT = worksheet->querySubObject("Range(QVariant, QVariant)",T);

                        cellU = worksheet->querySubObject("Range(QVariant, QVariant)",U);
                        cellV = worksheet->querySubObject("Range(QVariant, QVariant)",V);
                        cellW = worksheet->querySubObject("Range(QVariant, QVariant)",W);
                        cellX = worksheet->querySubObject("Range(QVariant, QVariant)",X);

                        cellY = worksheet->querySubObject("Range(QVariant, QVariant)",Y);
                        cellZ = worksheet->querySubObject("Range(QVariant, QVariant)",Z);
                        cellAA = worksheet->querySubObject("Range(QVariant, QVariant)",AA);
                        cellAB= worksheet->querySubObject("Range(QVariant, QVariant)",AB);

                        cellAC = worksheet->querySubObject("Range(QVariant, QVariant)",AC);
                        cellAD = worksheet->querySubObject("Range(QVariant, QVariant)",AD);
                        cellAE = worksheet->querySubObject("Range(QVariant, QVariant)",AE);
                        cellAF = worksheet->querySubObject("Range(QVariant, QVariant)",AF);
                        //设置单元格的表头值,列标题设置部分（例如吊杆、测点等）
                        cellA->dynamicCall("SetValue(const QVariant&)","时间");
                        cellB->dynamicCall("SetValue(const QVariant&)","测点名称");
                        cellC->dynamicCall("SetValue(const QVariant&)","应变变化值(με)");
                        cellD->dynamicCall("SetValue(const QVariant&)","温度(℃)");
                        cellrow++;

                        cellE->dynamicCall("SetValue(const QVariant&)","时间");
                        cellF->dynamicCall("SetValue(const QVariant&)","测点名称");
                        cellG->dynamicCall("SetValue(const QVariant&)","应变变化值(με)");
                        cellH->dynamicCall("SetValue(const QVariant&)","温度(℃)");
                        cellrow1++;

                        cellI->dynamicCall("SetValue(const QVariant&)","时间");
                        cellJ->dynamicCall("SetValue(const QVariant&)","测点名称");
                        cellK->dynamicCall("SetValue(const QVariant&)","应变变化值(με)");
                        cellL->dynamicCall("SetValue(const QVariant&)","温度(℃)");
                        cellrow2++;

                        cellM->dynamicCall("SetValue(const QVariant&)","时间");
                        cellN->dynamicCall("SetValue(const QVariant&)","测点名称");
                        cellO->dynamicCall("SetValue(const QVariant&)","应变变化值(με)");
                        cellP->dynamicCall("SetValue(const QVariant&)","温度(℃)");
                        cellrow3++;

                        cellQ->dynamicCall("SetValue(const QVariant&)","时间");
                        cellR->dynamicCall("SetValue(const QVariant&)","测点名称");
                        cellS->dynamicCall("SetValue(const QVariant&)","应变变化值(με)");
                        cellT->dynamicCall("SetValue(const QVariant&)","温度(℃)");
                        cellrow4++;

                        cellU->dynamicCall("SetValue(const QVariant&)","时间");
                        cellV->dynamicCall("SetValue(const QVariant&)","测点名称");
                        cellW->dynamicCall("SetValue(const QVariant&)","应变变化值(με)");
                        cellX->dynamicCall("SetValue(const QVariant&)","温度(℃)");
                        cellrow5++;

                        cellY->dynamicCall("SetValue(const QVariant&)","时间");
                        cellZ->dynamicCall("SetValue(const QVariant&)","测点名称");
                        cellAA->dynamicCall("SetValue(const QVariant&)","应变变化值(με)");
                        cellAB->dynamicCall("SetValue(const QVariant&)","温度(℃)");
                        cellrow6++;

                        cellAC->dynamicCall("SetValue(const QVariant&)","时间");
                        cellAD->dynamicCall("SetValue(const QVariant&)","测点名称");
                        cellAE->dynamicCall("SetValue(const QVariant&)","应变变化值(με)");
                        cellAF->dynamicCall("SetValue(const QVariant&)","温度(℃)");
                        cellrow7++;



                        QJsonArray dataArr=data.toArray();

                        //                    qDebug()<<"收到的数据是："<<dataArr;

                        //******************************************************************
                        // QJsonArray转换成QByteArray
                        //                                           QJsonDocument document=QJsonDocument(dataArr);
                        //                                           QByteArray byte_array = document.toJson();
                        //                                           saveMyData_test(byte_array,"all_file");
                        //**********************************************************************



                        //********************************************************************************存储信息进行excel转换
                        QString init_title[8]={
                            "东1测点","东2吊杆","北7测点","北8吊杆",
                            "南3测点","南4吊杆","西5测点","西6吊杆"
                        };
                        QString ss[8];
                        int sizes =dataArr.size();
                        for(int i=0;i<sizes;i++)
                        {
                            //                           MySaves.pointCode=dataArr.at(i).toObject().value("pointCode").toString();
                            //                           MySaves.pointName=dataArr.at(i).toObject().value("pointName").toString();
                            //                           MySaves.factorName=dataArr.at(i).toObject().value("factorName").toString();
                            QJsonArray list_arr=dataArr.at(i).toObject().value("listPhys").toArray();
                            int size_list = list_arr.size();
                            //拿取八个测点的名称
                            for(int g=0;g<8;g++)
                            {
                                ss[g]=dataArr.at(g).toObject().value("pointName").toString();
                            }
                            if(dataArr.at(i).toObject().value("pointName").toString()=="东1测点")
                            {
                                //                            diaogan.append(dataArr.at(i).toObject().value("pointName").toString());//存储吊杆信息

                                for(int j=0;j<size_list;j++)
                                {

                                    if(list_arr.at(j).toObject().value("phy").toString()=="应变变化值")
                                    {
                                        QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                        qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                        int my_num=sec_arr.size();
                                        nub1=my_num;
                                        for(int s=0;s<my_num;s++)
                                        {

                                            diaogan.append(dataArr.at(i).toObject().value("pointName").toString());//存储吊杆信息
                                            yingbianzhi.append(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                            shijian.append(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
                                        }
                                    }

                                    if(list_arr.at(j).toObject().value("phy").toString()=="温度")
                                    {
                                        QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                        qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                        int my_num=sec_arr.size();
                                        nub1=my_num;
                                        for(int s=0;s<my_num;s++)
                                        {

                                            wendu.append(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        }
                                    }

                                }


                            }

                            if(dataArr.at(i).toObject().value("pointName").toString()=="东2吊杆")
                            {
                                //                            diaogan.append(dataArr.at(i).toObject().value("pointName").toString());//存储吊杆信息

                                for(int j=0;j<size_list;j++)
                                {

                                    if(list_arr.at(j).toObject().value("phy").toString()=="应变变化值")
                                    {
                                        QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                        qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                        int my_num=sec_arr.size();
                                        nub=my_num;
                                        for(int s=0;s<my_num;s++)
                                        {

                                            diaogan.append(dataArr.at(i).toObject().value("pointName").toString());//存储吊杆信息
                                            yingbianzhi.append(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                            shijian.append(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
                                        }
                                    }

                                    if(list_arr.at(j).toObject().value("phy").toString()=="温度")
                                    {
                                        QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                        qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                        int my_num=sec_arr.size();
                                        nub1=my_num;
                                        for(int s=0;s<my_num;s++)
                                        {

                                            wendu.append(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        }
                                    }

                                }


                            }

                            if(dataArr.at(i).toObject().value("pointName").toString()=="北7测点")
                            {
                                //                            diaogan.append(dataArr.at(i).toObject().value("pointName").toString());//存储吊杆信息

                                for(int j=0;j<size_list;j++)
                                {

                                    if(list_arr.at(j).toObject().value("phy").toString()=="应变变化值")
                                    {
                                        QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                        qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                        int my_num=sec_arr.size();
                                        nub2=my_num;
                                        for(int s=0;s<my_num;s++)
                                        {

                                            diaogan.append(dataArr.at(i).toObject().value("pointName").toString());//存储吊杆信息
                                            yingbianzhi.append(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                            shijian.append(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
                                        }
                                    }

                                    if(list_arr.at(j).toObject().value("phy").toString()=="温度")
                                    {
                                        QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                        qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                        int my_num=sec_arr.size();
                                        nub2=my_num;
                                        for(int s=0;s<my_num;s++)
                                        {

                                            wendu.append(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        }
                                    }

                                }


                            }

                            if(dataArr.at(i).toObject().value("pointName").toString()=="北8吊杆")
                            {
                                //                            diaogan.append(dataArr.at(i).toObject().value("pointName").toString());//存储吊杆信息

                                for(int j=0;j<size_list;j++)
                                {

                                    if(list_arr.at(j).toObject().value("phy").toString()=="应变变化值")
                                    {
                                        QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                        qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                        int my_num=sec_arr.size();
                                        nub3=my_num;
                                        for(int s=0;s<my_num;s++)
                                        {

                                            diaogan.append(dataArr.at(i).toObject().value("pointName").toString());//存储吊杆信息
                                            yingbianzhi.append(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                            shijian.append(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
                                        }
                                    }

                                    if(list_arr.at(j).toObject().value("phy").toString()=="温度")
                                    {
                                        QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                        qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                        int my_num=sec_arr.size();
                                        nub3=my_num;
                                        for(int s=0;s<my_num;s++)
                                        {

                                            wendu.append(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        }
                                    }

                                }


                            }

                            if(dataArr.at(i).toObject().value("pointName").toString()=="南3测点")
                            {
                                //                            diaogan.append(dataArr.at(i).toObject().value("pointName").toString());//存储吊杆信息

                                for(int j=0;j<size_list;j++)
                                {

                                    if(list_arr.at(j).toObject().value("phy").toString()=="应变变化值")
                                    {
                                        QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                        qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                        int my_num=sec_arr.size();
                                        nub4=my_num;
                                        for(int s=0;s<my_num;s++)
                                        {

                                            diaogan.append(dataArr.at(i).toObject().value("pointName").toString());//存储吊杆信息
                                            yingbianzhi.append(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                            shijian.append(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
                                        }
                                    }

                                    if(list_arr.at(j).toObject().value("phy").toString()=="温度")
                                    {
                                        QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                        qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                        int my_num=sec_arr.size();
                                        nub4=my_num;
                                        for(int s=0;s<my_num;s++)
                                        {

                                            wendu.append(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        }
                                    }

                                }


                            }

                            if(dataArr.at(i).toObject().value("pointName").toString()=="南4吊杆")
                            {
                                //                            diaogan.append(dataArr.at(i).toObject().value("pointName").toString());//存储吊杆信息

                                for(int j=0;j<size_list;j++)
                                {

                                    if(list_arr.at(j).toObject().value("phy").toString()=="应变变化值")
                                    {
                                        QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                        qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                        int my_num=sec_arr.size();
                                        nub5=my_num;
                                        for(int s=0;s<my_num;s++)
                                        {

                                            diaogan.append(dataArr.at(i).toObject().value("pointName").toString());//存储吊杆信息
                                            yingbianzhi.append(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                            shijian.append(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
                                        }
                                    }

                                    if(list_arr.at(j).toObject().value("phy").toString()=="温度")
                                    {
                                        QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                        qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                        int my_num=sec_arr.size();
                                        nub5=my_num;
                                        for(int s=0;s<my_num;s++)
                                        {

                                            wendu.append(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        }
                                    }

                                }


                            }

                            if(dataArr.at(i).toObject().value("pointName").toString()=="西5测点")
                            {
                                //                            diaogan.append(dataArr.at(i).toObject().value("pointName").toString());//存储吊杆信息

                                for(int j=0;j<size_list;j++)
                                {

                                    if(list_arr.at(j).toObject().value("phy").toString()=="应变变化值")
                                    {
                                        QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                        qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                        int my_num=sec_arr.size();
                                        nub6=my_num;
                                        for(int s=0;s<my_num;s++)
                                        {

                                            diaogan.append(dataArr.at(i).toObject().value("pointName").toString());//存储吊杆信息
                                            yingbianzhi.append(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                            shijian.append(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
                                        }
                                    }

                                    if(list_arr.at(j).toObject().value("phy").toString()=="温度")
                                    {
                                        QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                        qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                        int my_num=sec_arr.size();
                                        nub6=my_num;
                                        for(int s=0;s<my_num;s++)
                                        {

                                            wendu.append(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        }
                                    }

                                }


                            }

                            if(dataArr.at(i).toObject().value("pointName").toString()=="西6吊杆")
                            {
                                //                            diaogan.append(dataArr.at(i).toObject().value("pointName").toString());//存储吊杆信息

                                for(int j=0;j<size_list;j++)
                                {

                                    if(list_arr.at(j).toObject().value("phy").toString()=="应变变化值")
                                    {
                                        QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                        qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                        int my_num=sec_arr.size();
                                        nub7=my_num;
                                        for(int s=0;s<my_num;s++)
                                        {

                                            diaogan.append(dataArr.at(i).toObject().value("pointName").toString());//存储吊杆信息
                                            yingbianzhi.append(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                            shijian.append(sec_arr.at(my_num - 1 - s).toObject().value("data_time").toString().mid(0,19));
                                        }
                                    }

                                    if(list_arr.at(j).toObject().value("phy").toString()=="温度")
                                    {
                                        QJsonArray sec_arr=list_arr.at(j).toObject().value("datas").toArray();
                                        qDebug()<<"获取到的值为数组大小："<<sizeof(sec_arr);
                                        int my_num=sec_arr.size();
                                        nub7=my_num;
                                        for(int s=0;s<my_num;s++)
                                        {

                                            wendu.append(sec_arr.at(my_num - 1 - s).toObject().value("data").toDouble());
                                        }
                                    }

                                }


                            }
                        }



                        //设置表格数据

                        //                    for(int s=0;s<nub1;s++)
                        //                    {
                        //                        QString C="C"+QString::number(cellrow);
                        //                        cellC = worksheet->querySubObject("Range(QVariant, QVariant)",C);
                        //                        cellC->dynamicCall("SetValue(const QVariant&)",wendu[s]);
                        //                        cellrow++;
                        //                    }

                        //                        for(int i=0;i<nub+nub1+nub2+nub3+nub4+nub5+nub6+nub7;i++){
                        //                            //设置要操作的单元格，如A1，A2，A3，A4
                        //                            QString A="A"+QString::number(cellrow);
                        //                            QString B="B"+QString::number(cellrow);
                        //                            QString C="C"+QString::number(cellrow);
                        //                            QString D="D"+QString::number(cellrow);
                        //                            //获取单元格
                        //                            cellA = worksheet->querySubObject("Range(QVariant, QVariant)",A);
                        //                            cellB = worksheet->querySubObject("Range(QVariant, QVariant)",B);
                        //                            cellC = worksheet->querySubObject("Range(QVariant, QVariant)",C);
                        //                            cellD = worksheet->querySubObject("Range(QVariant, QVariant)",D);
                        //                            //设置单元格的值,此处用数组代替循环添加数据
                        //                            cellA->dynamicCall("SetValue(const QVariant&)",diaogan[i]);
                        //                            cellB->dynamicCall("SetValue(const QVariant&)",shijian[i]);
                        //                            cellC->dynamicCall("SetValue(const QVariant&)",wendu[i]);
                        //                            cellD->dynamicCall("SetValue(const QVariant&)",yingbianzhi[i]);
                        //                            cellrow++;
                        //                        }
                        for(int i=0;i<nub;i++){
                            //设置要操作的单元格，如A1，A2，A3，A4
                            QString A="A"+QString::number(cellrow);
                            QString B="B"+QString::number(cellrow);
                            QString C="C"+QString::number(cellrow);
                            QString D="D"+QString::number(cellrow);
                            //获取单元格
                            cellA = worksheet->querySubObject("Range(QVariant, QVariant)",A);
                            cellB = worksheet->querySubObject("Range(QVariant, QVariant)",B);
                            cellC = worksheet->querySubObject("Range(QVariant, QVariant)",C);
                            cellD = worksheet->querySubObject("Range(QVariant, QVariant)",D);
                            //设置单元格的值,此处用数组代替循环添加数据
                            cellA->dynamicCall("SetValue(const QVariant&)",shijian[i]);
                            cellB->dynamicCall("SetValue(const QVariant&)",diaogan[i]);
                            cellC->dynamicCall("SetValue(const QVariant&)",yingbianzhi[i]);
                            cellD->dynamicCall("SetValue(const QVariant&)",wendu[i]);
                            cellrow++;
                        }
                        //西5测点值
                        for(int i=0;i<nub6;i++){
                            int dex=i+nub;
                            //设置要操作的单元格，如A1，A2，A3，A4
                            QString E="E"+QString::number(cellrow1);
                            QString F="F"+QString::number(cellrow1);
                            QString G="G"+QString::number(cellrow1);
                            QString H="H"+QString::number(cellrow1);
                            //获取单元格
                            cellE = worksheet->querySubObject("Range(QVariant, QVariant)",E);
                            cellF = worksheet->querySubObject("Range(QVariant, QVariant)",F);
                            cellG = worksheet->querySubObject("Range(QVariant, QVariant)",G);
                            cellH = worksheet->querySubObject("Range(QVariant, QVariant)",H);
                            //设置单元格的值,此处用数组代替循环添加数据
                            cellE->dynamicCall("SetValue(const QVariant&)",shijian[dex]);
                            cellF->dynamicCall("SetValue(const QVariant&)",diaogan[dex]);
                            cellG->dynamicCall("SetValue(const QVariant&)",yingbianzhi[dex]);
                            cellH->dynamicCall("SetValue(const QVariant&)",wendu[dex]);
                            cellrow1++;
                        }

                        //西6
                        for(int i=0;i<nub7;i++){
                            int dex=i+nub+nub6;
                            //设置要操作的单元格，如A1，A2，A3，A4
                            QString I="I"+QString::number(cellrow2);
                            QString J="J"+QString::number(cellrow2);
                            QString K="K"+QString::number(cellrow2);
                            QString L="L"+QString::number(cellrow2);
                            //获取单元格
                            cellI = worksheet->querySubObject("Range(QVariant, QVariant)",I);
                            cellJ = worksheet->querySubObject("Range(QVariant, QVariant)",J);
                            cellK = worksheet->querySubObject("Range(QVariant, QVariant)",K);
                            cellL = worksheet->querySubObject("Range(QVariant, QVariant)",L);
                            //设置单元格的值,此处用数组代替循环添加数据
                            cellI->dynamicCall("SetValue(const QVariant&)",shijian[dex]);
                            cellJ->dynamicCall("SetValue(const QVariant&)",diaogan[dex]);
                            cellK->dynamicCall("SetValue(const QVariant&)",yingbianzhi[dex]);
                            cellL->dynamicCall("SetValue(const QVariant&)",wendu[dex]);
                            cellrow2++;
                        }
                        //北8--3
                        for(int i=0;i<nub3;i++){
                            int dex=i+nub+nub6+nub7;
                            //设置要操作的单元格，如A1，A2，A3，A4
                            QString M="M"+QString::number(cellrow3);
                            QString N="N"+QString::number(cellrow3);
                            QString O="O"+QString::number(cellrow3);
                            QString P="P"+QString::number(cellrow3);
                            //获取单元格
                            cellM = worksheet->querySubObject("Range(QVariant, QVariant)",M);
                            cellN = worksheet->querySubObject("Range(QVariant, QVariant)",N);
                            cellO = worksheet->querySubObject("Range(QVariant, QVariant)",O);
                            cellP = worksheet->querySubObject("Range(QVariant, QVariant)",P);
                            //设置单元格的值,此处用数组代替循环添加数据
                            cellM->dynamicCall("SetValue(const QVariant&)",shijian[dex]);
                            cellN->dynamicCall("SetValue(const QVariant&)",diaogan[dex]);
                            cellO->dynamicCall("SetValue(const QVariant&)",yingbianzhi[dex]);
                            cellP->dynamicCall("SetValue(const QVariant&)",wendu[dex]);
                            cellrow3++;
                        }
                        //东1--1
                        for(int i=0;i<nub1;i++){
                            int dex=i+nub+nub6+nub7+nub3;
                            //设置要操作的单元格，如A1，A2，A3，A4
                            QString Q="Q"+QString::number(cellrow4);
                            QString R="R"+QString::number(cellrow4);
                            QString S="S"+QString::number(cellrow4);
                            QString T="T"+QString::number(cellrow4);
                            //获取单元格
                            cellQ = worksheet->querySubObject("Range(QVariant, QVariant)",Q);
                            cellR = worksheet->querySubObject("Range(QVariant, QVariant)",R);
                            cellS = worksheet->querySubObject("Range(QVariant, QVariant)",S);
                            cellT = worksheet->querySubObject("Range(QVariant, QVariant)",T);
                            //设置单元格的值,此处用数组代替循环添加数据
                            cellQ->dynamicCall("SetValue(const QVariant&)",shijian[dex]);
                            cellR->dynamicCall("SetValue(const QVariant&)",diaogan[dex]);
                            cellS->dynamicCall("SetValue(const QVariant&)",yingbianzhi[dex]);
                            cellT->dynamicCall("SetValue(const QVariant&)",wendu[dex]);
                            cellrow4++;
                        }
                        //南3--4
                        for(int i=0;i<nub4;i++){
                            int dex=i+nub+nub6+nub7+nub3+nub1;
                            //设置要操作的单元格，如A1，A2，A3，A4
                            QString U="U"+QString::number(cellrow5);
                            QString V="V"+QString::number(cellrow5);
                            QString W="W"+QString::number(cellrow5);
                            QString X="X"+QString::number(cellrow5);
                            //获取单元格
                            cellU = worksheet->querySubObject("Range(QVariant, QVariant)",U);
                            cellV = worksheet->querySubObject("Range(QVariant, QVariant)",V);
                            cellW = worksheet->querySubObject("Range(QVariant, QVariant)",W);
                            cellX = worksheet->querySubObject("Range(QVariant, QVariant)",X);
                            //设置单元格的值,此处用数组代替循环添加数据
                            cellU->dynamicCall("SetValue(const QVariant&)",shijian[dex]);
                            cellV->dynamicCall("SetValue(const QVariant&)",diaogan[dex]);
                            cellW->dynamicCall("SetValue(const QVariant&)",yingbianzhi[dex]);
                            cellX->dynamicCall("SetValue(const QVariant&)",wendu[dex]);
                            cellrow5++;
                        }
                        //北7--2
                        for(int i=0;i<nub2;i++){
                            int dex=i+nub+nub6+nub7+nub3+nub1+nub4;
                            //设置要操作的单元格，如A1，A2，A3，A4
                            QString Y="Y"+QString::number(cellrow6);
                            QString Z="Z"+QString::number(cellrow6);
                            QString AA="AA"+QString::number(cellrow6);
                            QString AB="AB"+QString::number(cellrow6);
                            //获取单元格
                            cellY = worksheet->querySubObject("Range(QVariant, QVariant)",Y);
                            cellZ = worksheet->querySubObject("Range(QVariant, QVariant)",Z);
                            cellAA = worksheet->querySubObject("Range(QVariant, QVariant)",AA);
                            cellAB = worksheet->querySubObject("Range(QVariant, QVariant)",AB);
                            //设置单元格的值,此处用数组代替循环添加数据
                            cellY->dynamicCall("SetValue(const QVariant&)",shijian[dex]);
                            cellZ->dynamicCall("SetValue(const QVariant&)",diaogan[dex]);
                            cellAA->dynamicCall("SetValue(const QVariant&)",yingbianzhi[dex]);
                            cellAB->dynamicCall("SetValue(const QVariant&)",wendu[dex]);
                            cellrow6++;
                        }
                        //南4--5
                        for(int i=0;i<nub5;i++){
                            int dex=i+nub+nub6+nub7+nub3+nub1+nub4+nub2;
                            //设置要操作的单元格，如A1，A2，A3，A4
                            QString AC="AC"+QString::number(cellrow7);
                            QString AD="AD"+QString::number(cellrow7);
                            QString AE="AE"+QString::number(cellrow7);
                            QString AF="AF"+QString::number(cellrow7);
                            //获取单元格
                            cellAC = worksheet->querySubObject("Range(QVariant, QVariant)",AC);
                            cellAD = worksheet->querySubObject("Range(QVariant, QVariant)",AD);
                            cellAE = worksheet->querySubObject("Range(QVariant, QVariant)",AE);
                            cellAF = worksheet->querySubObject("Range(QVariant, QVariant)",AF);
                            //设置单元格的值,此处用数组代替循环添加数据
                            cellAC->dynamicCall("SetValue(const QVariant&)",shijian[dex]);
                            cellAD->dynamicCall("SetValue(const QVariant&)",diaogan[dex]);
                            cellAE->dynamicCall("SetValue(const QVariant&)",yingbianzhi[dex]);
                            cellAF->dynamicCall("SetValue(const QVariant&)",wendu[dex]);
                            cellrow7++;
                        }
                        

                        workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(filepath));//保存至filepath，注意一定要用QDir::toNativeSeparators将路径中的"/"转换为"\"，不然一定保存不了。

                        workbook->dynamicCall("Close()");//关闭工作簿
                        excel->dynamicCall("Quit()");//关闭excel
                        delete excel;
                        excel=NULL;
                        qDebug() << "\n导出成功啦！！！";
                        QMessageBox::warning(this,tr("下载成功啦！"),tr("导出成功啦！!"));
                        ui->pushButton_5->setEnabled(true);
                        ui->pushButton_5->setText("下载");


                    }
                    ui->pushButton_5->setText("下载");
                    ui->pushButton_5->setEnabled(true);
                }
                //            update_plot();



            }
        }

    }

}





//测试使用保存txt文件函数
void TestPoint_Info::saveMyData_test(QByteArray Mydata,QString Myname)
{
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


void TestPoint_Info::skipSave_excl()
{
    //获取保存路径
    QString filepath=QFileDialog::getSaveFileName(this,tr("Save"),".",tr(" (*.xlsx)"));
    if(!filepath.isEmpty()){
        QAxObject *excel = new QAxObject(this);
        //连接Excel控件
        excel->setControl("Excel.Application");
        //不显示窗体
        excel->dynamicCall("SetVisible (bool Visible)","false");
        //不显示任何警告信息。如果为true那么在关闭是会出现类似“文件已修改，是否保存”的提示
        excel->setProperty("DisplayAlerts", false);
        //获取工作簿集合
        QAxObject *workbooks = excel->querySubObject("WorkBooks");
        //新建一个工作簿
        workbooks->dynamicCall("Add");
        //获取当前工作簿
        QAxObject *workbook = excel->querySubObject("ActiveWorkBook");
        //获取工作表集合
        QAxObject *worksheets = workbook->querySubObject("Sheets");
        //获取工作表集合的工作表1，即sheet1
        QAxObject *worksheet = worksheets->querySubObject("Item(int)",1);

        QAxObject *cellA,*cellB,*cellC,*cellD;
        //设置标题
        int cellrow=1;
        //设置要操作的单元格，如A1
        QString A="A"+QString::number(cellrow);
        QString B="B"+QString::number(cellrow);
        QString C="C"+QString::number(cellrow);
        QString D="D"+QString::number(cellrow);
        //获取单元格
        cellA = worksheet->querySubObject("Range(QVariant, QVariant)",A);
        cellB = worksheet->querySubObject("Range(QVariant, QVariant)",B);
        cellC = worksheet->querySubObject("Range(QVariant, QVariant)",C);
        cellD = worksheet->querySubObject("Range(QVariant, QVariant)",D);
        //设置单元格的表头值,列标题设置部分（例如吊杆、测点等）
        cellA->dynamicCall("SetValue(const QVariant&)",7);
        cellB->dynamicCall("SetValue(const QVariant&)",7);
        cellC->dynamicCall("SetValue(const QVariant&)",7);
        cellD->dynamicCall("SetValue(const QVariant&)",7);
        cellrow++;
        int nub = 40;
        //设置表格数据
        for(int i=0;i<nub;i++){
            //设置要操作的单元格，如A1，A2，A3，A4
            QString A="A"+QString::number(cellrow);
            QString B="B"+QString::number(cellrow);
            QString C="C"+QString::number(cellrow);
            QString D="D"+QString::number(cellrow);
            //获取单元格
            cellA = worksheet->querySubObject("Range(QVariant, QVariant)",A);
            cellB = worksheet->querySubObject("Range(QVariant, QVariant)",B);
            cellC = worksheet->querySubObject("Range(QVariant, QVariant)",C);
            cellD = worksheet->querySubObject("Range(QVariant, QVariant)",D);
            //设置单元格的值
            cellA->dynamicCall("SetValue(const QVariant&)",1);
            cellB->dynamicCall("SetValue(const QVariant&)",2);
            cellC->dynamicCall("SetValue(const QVariant&)",3);
            cellD->dynamicCall("SetValue(const QVariant&)",4);
            cellrow++;
        }

        workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(filepath));//保存至filepath，注意一定要用QDir::toNativeSeparators将路径中的"/"转换为"\"，不然一定保存不了。
        workbook->dynamicCall("Close()");//关闭工作簿
        excel->dynamicCall("Quit()");//关闭excel
        delete excel;
        excel=NULL;
        qDebug() << "\n导出成功啦！！！";
    }

}
