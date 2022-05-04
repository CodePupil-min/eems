#include "page_data.h"
#include "ui_page_data.h"

page_data::page_data(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page_data)
{
    ui->setupUi(this);
}

page_data::~page_data()
{
    delete ui;
}
