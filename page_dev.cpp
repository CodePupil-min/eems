#include "page_dev.h"
#include "ui_page_dev.h"

page_dev::page_dev(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page_dev)
{
    ui->setupUi(this);
    //一些初始的ui
    iconFont=(new Tool())->getIconFont();
    ui->logo->setFont(iconFont);
    ui->logo->setText(_icon_dev);
}

page_dev::~page_dev()
{
    delete ui;
}
void page_dev::setTitle(bool isLogin){
    QString title=isLogin?"设备控制":"设备控制(登录后可用)";
    ui->title->setText(title);
}
void page_dev::setCurrentPort(QSerialPort** port){
    currentport=*port;
    connect(ui->send,&QPushButton::clicked,this,&page_dev::sendPortMsg);
}
void page_dev::sendPortMsg(){
    if(currentport==nullptr)return;
    currentport->write(ui->info->text().toLocal8Bit());
}
