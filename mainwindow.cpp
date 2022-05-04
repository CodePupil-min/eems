#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*设置图标字体*/
    int fontId = QFontDatabase::addApplicationFont(":/font/fa-solid-900.ttf"); //加入字体，并获取字体ID
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0); //获取字体名称
    iconFont = QFont(fontName);
    setMenuButton();
    /*次级页面*/
    p_env=new page_env(this);
    p_dev=new page_dev(this);
    p_data=new page_data(this);
    p_net=new page_net(this);
    //将每个页面添加进去
    ui->mainPage->addWidget(p_env);
    ui->mainPage->addWidget(p_dev);
    ui->mainPage->addWidget(p_data);
    ui->mainPage->addWidget(p_net);
    //设置环境检测为主界面
    ui->mainPage->setCurrentWidget(this->p_env);
    //按钮和界面联系起来
    connect(ui->menu_env,&QPushButton::clicked,this,&MainWindow::chooseEnvP);
    connect(ui->menu_dev,&QPushButton::clicked,this,&MainWindow::chooseDevP);
    connect(ui->menu_data,&QPushButton::clicked,this,&MainWindow::chooseDataP);
    connect(ui->menu_net,&QPushButton::clicked,this,&MainWindow::chooseNetP);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::chooseEnvP(){
    ui->mainPage->setCurrentWidget(this->p_env);
}
void MainWindow::chooseDevP(){
    ui->mainPage->setCurrentWidget(this->p_dev);
}
void MainWindow::chooseDataP(){
    ui->mainPage->setCurrentWidget(this->p_data);
}
void MainWindow::chooseNetP(){
    ui->mainPage->setCurrentWidget(this->p_net);
}
void MainWindow::setMenuButton(){
    ui->menu_env->setFont(iconFont); //设置字体
    ui->menu_env->installEventFilter(this);
    ui->menu_env->setText(QChar(0xf06c));

    ui->menu_dev->setFont(iconFont); //设置字体
    ui->menu_dev->installEventFilter(this);
    ui->menu_dev->setText(QChar(0xf0e8));

    ui->menu_data->setFont(iconFont); //设置字体
    ui->menu_data->installEventFilter(this);
    ui->menu_data->setText(QChar(0xf1c0));

    ui->menu_net->setFont(iconFont); //设置字体
    ui->menu_net->installEventFilter(this);
    ui->menu_net->setText(QChar(0xf1eb));

    ui->menu_exit->setFont(iconFont); //设置字体
    ui->menu_exit->installEventFilter(this);
    ui->menu_exit->setText(QChar(0xf2f5));
}
////事件过滤器
bool MainWindow::eventFilter(QObject *obj,QEvent *event)
{
    if(obj == ui->menu_env) {
        QString str1=QChar(0xf06c);
        QString str2="环境\n监测";
        if(event->type() == QEvent::HoverEnter) {
            ui->menu_env->setText(str2);
            return true;
        }
        else if(event->type() == QEvent::HoverLeave) {
            ui->menu_env->setText(str1);
        }
    }
    if(obj == ui->menu_dev) {
        QString str1=QChar(0xf0e8);
        QString str2="设备\n管理";
        if(event->type() == QEvent::HoverEnter) {
            ui->menu_dev->setText(str2);
            return true;
        }
        else if(event->type() == QEvent::HoverLeave) {
            ui->menu_dev->setText(str1);
        }
    }
    if(obj == ui->menu_data) {
        QString str1=QChar(0xf1c0);
        QString str2="数据\n管理";
        if(event->type() == QEvent::HoverEnter) {
            ui->menu_data->setText(str2);
            return true;
        }
        else if(event->type() == QEvent::HoverLeave) {
            ui->menu_data->setText(str1);
        }
    }
    if(obj == ui->menu_net) {
        QString str1=QChar(0xf1eb);
        QString str2="网络\n连接";
        if(event->type() == QEvent::HoverEnter) {
            ui->menu_net->setText(str2);
            return true;
        }
        else if(event->type() == QEvent::HoverLeave) {
            ui->menu_net->setText(str1);
        }
    }
    if(obj == ui->menu_exit) {
        QString str1=QChar(0xf2f5);
        QString str2="退出";
        if(event->type() == QEvent::HoverEnter) {
            ui->menu_exit->setText(str2);
            return true;
        }
        else if(event->type() == QEvent::HoverLeave) {
            ui->menu_exit->setText(str1);
        }
    }
    return QWidget::eventFilter(obj,event);
}

