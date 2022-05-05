/*主界面*/
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
    p_super=new page_super(this);
    d_login=new dialog_login(this);
    //将每个页面添加进去
    ui->mainPage->addWidget(p_env);
    ui->mainPage->addWidget(p_dev);
    ui->mainPage->addWidget(p_data);
    ui->mainPage->addWidget(p_net);
    ui->mainPage->addWidget(p_super);
    //设置环境检测为主界面
    ui->mainPage->setCurrentWidget(this->p_env);
    //按钮和界面联系起来
    connect(ui->menu_env,&QPushButton::clicked,this,&MainWindow::chooseEnvP);
    connect(ui->menu_dev,&QPushButton::clicked,this,&MainWindow::chooseDevP);
    connect(ui->menu_data,&QPushButton::clicked,this,&MainWindow::chooseDataP);
    connect(ui->menu_net,&QPushButton::clicked,this,&MainWindow::chooseNetP);
    connect(ui->menu_exit,&QPushButton::clicked,this,&MainWindow::pressExit);
    updateUserStatus();//更新登录状态
    connect(d_login,&dialog_login::loginSuccess,this,&MainWindow::loginSuccess);//登陆成功更新状态
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
void MainWindow::manageUsers(){
    ui->mainPage->setCurrentWidget(this->p_super);
}
void MainWindow::login(){
    d_login->show();
}

void MainWindow::pressExit(){
    isLogin=false;
    isSuper=false;
    ui->mainPage->setCurrentWidget(this->p_env);
    updateUserStatus();
}
void MainWindow::setMenuButton(){
    ui->menu_env->setFont(iconFont); //设置字体
    ui->menu_env->installEventFilter(this);
    ui->menu_env->setText(_icon_env);

    ui->menu_dev->setFont(iconFont); //设置字体
    ui->menu_dev->installEventFilter(this);
    ui->menu_dev->setText(_icon_dev);

    ui->menu_data->setFont(iconFont); //设置字体
    ui->menu_data->installEventFilter(this);
    ui->menu_data->setText(_icon_data);

    ui->menu_net->setFont(iconFont); //设置字体
    ui->menu_net->installEventFilter(this);
    ui->menu_net->setText(_icon_net);

    ui->menu_exit->setFont(iconFont); //设置字体
    ui->menu_exit->installEventFilter(this);
    ui->menu_exit->setText(_icon_exit);

    ui->user->setFont(iconFont); //设置字体
    ui->user->installEventFilter(this);
    if(isLogin)ui->user->setText(isSuper?_icon_super:_icon_user);
    else ui->user->setText(_icon_not_login);
}
//事件过滤器
bool MainWindow::eventFilter(QObject *obj,QEvent *event)
{
    if(obj == ui->menu_env) {
        QString str1=_icon_env;
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
        QString str1=_icon_dev;
        QString str2="设备\n控制";
        if(event->type() == QEvent::HoverEnter) {
            ui->menu_dev->setText(str2);
            return true;
        }
        else if(event->type() == QEvent::HoverLeave) {
            ui->menu_dev->setText(str1);
        }
    }
    if(obj == ui->menu_data) {
        QString str1=_icon_data;
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
        QString str1=_icon_net;
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
        QString str1=_icon_exit;
        QString str2="退出\n登录";
        if(event->type() == QEvent::HoverEnter) {
            ui->menu_exit->setText(str2);
            return true;
        }
        else if(event->type() == QEvent::HoverLeave) {
            ui->menu_exit->setText(str1);
        }
    }
    if(obj == ui->user) {
        QString str1=_icon_not_login;
        QString str2="未登录";
        if(isLogin){
            str1=isSuper?_icon_super:_icon_user;
            str2=username;
        }
        if(event->type() == QEvent::HoverEnter) {
            ui->user->setText(str2);
            return true;
        }
        else if(event->type() == QEvent::HoverLeave) {
            ui->user->setText(str1);
        }
    }
    return QWidget::eventFilter(obj,event);
}

void MainWindow::updateUserStatus(){
    disconnect(ui->user,&QPushButton::clicked,0,0);
    if(!isLogin){//未登录不能控制设备
        connect(ui->user,&QPushButton::clicked,this,&MainWindow::login);
        for(QPushButton*btn:p_dev->findChildren<QPushButton *>())
            btn->setEnabled(false);
        ui->user->setText(_icon_not_login);
        return;
    }
    for(QPushButton*btn:p_dev->findChildren<QPushButton *>())//登陆后使能dev按钮
        btn->setEnabled(true);
    if(isSuper){//管理员
        connect(ui->user,&QPushButton::clicked,this,&MainWindow::manageUsers);
        ui->user->setText(_icon_super);
    }
    else {
        ui->user->setText(_icon_user);
    }
}

void MainWindow::loginSuccess(){
    isLogin=d_login->isLogin;
    isSuper=d_login->isSuper;
    username=d_login->username;
    updateUserStatus();
}
