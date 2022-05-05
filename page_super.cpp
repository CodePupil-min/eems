#include "page_super.h"
#include "ui_page_super.h"

page_super::page_super(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page_super)
{
    ui->setupUi(this);
}

page_super::~page_super()
{
    delete ui;
}
