#include "page_net.h"
#include "ui_page_net.h"

page_net::page_net(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page_net)
{
    ui->setupUi(this);
}

page_net::~page_net()
{
    delete ui;
}
