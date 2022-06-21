#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QWidget>
#include "contents.h"
#include "qcustomplot.h"
//#include "contents.h"
class Contents;
namespace Ui {
class HomePage;
}

class HomePage : public QWidget
{
    Q_OBJECT

public:
    explicit HomePage(QWidget *parent = nullptr);
    ~HomePage();

    void set_content(Contents* pwidget);
private slots:

    void on_WestLeft_clicked();

    void on_WestSouth_clicked();

    void on_EastSouth_clicked();

    void on_EastNorth_clicked();

    void on_WestLeft_1_clicked();

    void on_WestSouth_1_clicked();

    void on_EastSouth_1_clicked();

    void on_EastNorth_1_clicked();

signals:
    void Get_info(QString info);

private:
    Ui::HomePage *ui;

    Contents *content_1;

};

#endif // HOMEPAGE_H
