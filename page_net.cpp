#include "page_net.h"
#include "ui_page_net.h"

page_net::page_net(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page_net)
{
    ui->setupUi(this);
    //一些初始的ui
    iconFont=(new Tool())->getIconFont();
    ui->logo->setFont(iconFont);
    ui->logo->setText(_icon_net);
}

page_net::~page_net()
{
    delete ui;
}
