#include "page_data.h"
#include "ui_page_data.h"

page_data::page_data(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page_data)
{
    ui->setupUi(this);
    //一些初始的ui
    iconFont=(new Tool())->getIconFont();
    ui->logo->setFont(iconFont);
    ui->logo->setText(_icon_data);
}

page_data::~page_data()
{
    delete ui;
}
