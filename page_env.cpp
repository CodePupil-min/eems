#include "page_env.h"
#include "ui_page_env.h"

page_env::page_env(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page_env)
{
    ui->setupUi(this);
}

page_env::~page_env()
{
    delete ui;
}
