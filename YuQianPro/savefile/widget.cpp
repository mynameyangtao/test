#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QMessageBox>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug()<<ui->AccountNum_Edit;

    content=new Contents();
    homepage_cope=new HomePage();
    his=new HistoryCharts();
    test_info=new TestPoint_Info();


    isLogin = false;
    //    ui->pushButton_2->setEnabled(false);
    httpLogin = new QNetworkAccessManager(this);
    projectCode = 1552;
    // 绑定请求完成信号和完成后的操作
    connect(httpLogin, SIGNAL(finished(QNetworkReply *)), this, SLOT(loginSuccess(QNetworkReply *)));

    connect(this,SIGNAL(send_datas(QString)),his,SLOT(receive_data(QString)));

    connect(this,SIGNAL(send_datas_down(QString)),test_info,SLOT(receive_data_down(QString)));

    setWindowTitle("德岭软件 v1.1");
    setFixedSize(800,500);
    ui->PassWorld_Edit->setEchoMode(QLineEdit::Password);

    //设置账号、密码提示
    ui->AccountNum_Edit->setPlaceholderText("请 输 入 账 号 （数 字）");
    ui->PassWorld_Edit->setPlaceholderText("请 输 入 密 码 （数 字）");

    ui->pushButton->setFocus();    //设置默认焦点
    ui->pushButton->setShortcut( QKeySequence::InsertParagraphSeparator );  //设置快捷键为键盘的“回车”键
    ui->pushButton->setShortcut(Qt::Key_Enter);  //设置快捷键为enter键
    ui->pushButton->setShortcut(Qt::Key_Return); //设置快捷键为小键盘上的enter键



}

Widget::~Widget()
{
    delete ui;
}




//QString Widget::getToken()
//{
//    return strToken;
//}

void Widget::on_pushButton_clicked()
{
    qDebug()<<"按下确认键！";
    QString url = "https://www.everiaction.com/IOT-ADAPTER-CUSTOM/auth/anon/login";
    // https需要的配置
    QNetworkRequest reqLogin;
    QSslConfiguration sslConf = reqLogin.sslConfiguration();
    sslConf.setPeerVerifyMode(QSslSocket::VerifyNone);
    sslConf.setProtocol(QSsl::TlsV1SslV3);
    reqLogin.setSslConfiguration(sslConf);
    //指定url
    reqLogin.setUrl(QUrl(url));
    // 设置header
    reqLogin.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));

    QJsonObject json;
    json.insert("username",ui->AccountNum_Edit->text());
    json.insert("password",ui->PassWorld_Edit->text());
    QJsonDocument document;
    document.setObject(json);
    //发送数据
    httpLogin->post(reqLogin, document.toJson());



    //    //判断信息是否正常，作出反应
    //    if(ui->PassWorld_Edit->text()=="123456")
    //    {
    //        qDebug()<<"密码输入正确！";
    //    }
    //    else if(ui->PassWorld_Edit->text()=="")
    //    {
    //        qDebug()<<"密码输入不能为空！";
    //        QMessageBox::warning(ui->PassWorld_Edit, "warning", "密码输入不能为空！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    //    }
    //    else
    //    {
    //        qDebug()<<"密码输入错误！";
    //        QMessageBox::critical(ui->PassWorld_Edit, "critical", "密码输入错误！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    //        ui->PassWorld_Edit->setText("");
    //    }

    //    if(ui->AccountNum_Edit->text()=="88888888")
    //    {
    //        qDebug()<<"账号输入正确！";
    //    }
    //    else if(ui->AccountNum_Edit->text()=="")
    //    {
    //        qDebug()<<"账号输入不能为空！";
    //        QMessageBox::warning(ui->AccountNum_Edit, "warning", "账号输入不能为空！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    //    }
    //    else
    //    {
    //        qDebug()<<"输入账号不正确！";
    //        QMessageBox::critical(ui->AccountNum_Edit, "success!", "输入账号不正确！", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    //    }

    if(ui->AccountNum_Edit->text()=="88888888" && ui->PassWorld_Edit->text()=="123456")
    {
        this->hide();

        content=new Contents();
        content->show();
        QMessageBox::information(ui->AccountNum_Edit, "登录成功！", "登录成功！",
                                 QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);


    }

}


int Widget::loginSuccess(QNetworkReply *reply)
{

    //    Contents *w = new Contents;
    //    HistoryCharts *his = new HistoryCharts;

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
            // 转为Json对象
            QJsonObject json = document.object();
            // 取状态的值
            QJsonValue status = json.value("status");



            //TODO
            if(status.toInt()==500)
            {
                qDebug()<<"输入账号不正确！";
                QMessageBox::critical(ui->AccountNum_Edit, "error!", "输入密码或账号不正确！", QMessageBox::Yes |  QMessageBox::Yes);
                return 0;
            }
            if  (status.toInt() != 200)
            {

                return 0;
            }


            QJsonValue data = json.value("data");

            // 检查值是否存在
            //longin
            if (data.isObject())
            {

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


                his->send_Token_Data(strToken);



                qDebug() << "token:" << strToken;
                qDebug() << "projectCode:" << projectCode;
                qDebug() << "Login success !!!";
                if (!strToken.isEmpty())
                {
                    //                        ui->pushButton_2->setEnabled(true);
                    isLogin = true;
                    //                        return true;

                    QMessageBox box(QMessageBox::Information, "提示"," 登录成功！");
                    box.setStandardButtons(QMessageBox::Ok | QMessageBox::No);
                    box.setButtonText(QMessageBox::Ok, QString("确认"));
                    box.setButtonText(QMessageBox::No, QString("取消"));
                    //                        box.setButtonText(QMessageBox::Cancel, QString("取 消"));
                    int button = box.exec();
                    if (button == QMessageBox::Ok)
                    {

                        content->sendData(strToken); //strToken调用给content
                        test_info->down_receive_Data(strToken);
                        emit send_datas(strToken);
                        emit send_datas_down(strToken);
                        this->close();
                        //                        content->show();
                        homepage_cope->set_content(content);
                        homepage_cope->show();
                    }
                    else if(button == QMessageBox::No)
                    {
                        return 0;
                    }
                }
                else
                {
                    qDebug() << "Login failure !!!";
                }
            }
            else if (data.isArray())
            {
                //                    QJsonArray dataArr = data.toArray();

            }


        }
    }
}





