#include "confirm.h"
#include "ui_confirm.h"

confirm::confirm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::confirm)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);
    connect(ui->ok,&QPushButton::clicked,this,&confirm::pressOK);
    connect(ui->nok,&QPushButton::clicked,this,&confirm::pressNOK);
}
confirm::~confirm()
{
    delete ui;
}
void confirm::pressOK(){
    this->accept();
}
void confirm::pressNOK(){
    this->reject();
}
bool confirm::reveal(QString message,QChar title, bool onebtn){
    ui->title->setFont((new Tool())->getIconFont()); //设置字体
    ui->message->setText(message);
    if(title!=QChar(0))ui->title->setText(title);
    if(onebtn)ui->nok->hide();
    return this->exec();
}

