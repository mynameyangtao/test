#include "homepage.h"
#include "ui_homepage.h"

HomePage::HomePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomePage)
{
    ui->setupUi(this);
    setWindowTitle("德岭软件 v1.1");
    //    content_1=new Contents();



    ui->label->setAttribute(Qt::WA_TranslucentBackground);//设置子窗口为透明背景色
    //    ui->label->setAttribute(Qt::WA_TranslucentBackground);//设置子窗口为透明背景色；
    //    ui->widget_3->setStyleSheet("border-image:url(:/back/image/mybackgroundimage.jpg)");
    //    ui->widget->setStyleSheet("image: url(:/back/image/HangingBasket.jpg)");
    //    ui->pushButton->setAttribute(Qt::WA_TranslucentBackground);//设置子窗口为透明背景色
    //    ui->pushButton->setStyleSheet("border-image:url(:/back/image/BG.jpg)");

}

HomePage::~HomePage()
{
    delete ui;
}


void HomePage::set_content(Contents *pwidget)
{
    content_1 = pwidget;
    connect(this,SIGNAL(Get_info(QString)),content_1,SLOT(Receive(QString)));
    content_1->set_conten_homet(this);
}

void HomePage::on_WestLeft_clicked()
{
    //每个按钮都发送该信号 把信息传递给contents页面，然后在contents页面中进行判断
    this->hide();
    emit Get_info(ui->WestLeft->text());
    content_1->show();
}

void HomePage::on_WestSouth_clicked()
{
    this->hide();
    emit Get_info(ui->WestSouth->text());
    content_1->show();
}

void HomePage::on_EastSouth_clicked()
{
    this->hide();
    emit Get_info(ui->EastSouth->text());
    content_1->show();
}

void HomePage::on_EastNorth_clicked()
{
    this->hide();
    emit Get_info(ui->EastNorth->text());
    content_1->show();
}

void HomePage::on_WestLeft_1_clicked()
{
    this->hide();
    emit Get_info(ui->WestLeft_1->text());
    content_1->show();
}

void HomePage::on_WestSouth_1_clicked()
{
    this->hide();
    emit Get_info(ui->WestSouth_1->text());
    content_1->show();
}

void HomePage::on_EastSouth_1_clicked()
{
    this->hide();
    emit Get_info(ui->EastSouth_1->text());
    content_1->show();
}

void HomePage::on_EastNorth_1_clicked()
{
    this->hide();
    emit Get_info(ui->EastNorth_1->text());
    content_1->show();
}
