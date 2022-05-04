#include "page_dev.h"
#include "ui_page_dev.h"

page_dev::page_dev(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page_dev)
{
    ui->setupUi(this);
}

page_dev::~page_dev()
{
    delete ui;
}
