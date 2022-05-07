#include "dialog_login.h"
#include "ui_dialog_login.h"

dialog_login::dialog_login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_login)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Dialog);
    //连接按钮
    connect(ui->login,&QPushButton::clicked,this,&dialog_login::pressLogin);
    connect(ui->cancel,&QPushButton::clicked,this,&dialog_login::pressCancel);
    db=new database();//建立数据库连接操作

    QFont iconFont=(new Tool())->getIconFont();
    ui->usericon->setFont(iconFont); //设置图标
    ui->usericon->setText(_icon_user);
    ui->pwdicon->setFont(iconFont); //设置图标
    ui->pwdicon->setText(_icon_key);
    ui->info->hide();
}

dialog_login::~dialog_login()
{
    delete ui;
}
void dialog_login::pressLogin(){
    isLogin=isSuper=false;
    QString user=ui->username->text();
    QString pwd=ui->password->text();
    if(db->isUserExist(user)){
        if(db->isPwdTrue(pwd)){
            isLogin=true;
            isSuper=db->isSuperUser();//是否管理员
            username=isSuper?"管理员":user;
        }
        else{
            ui->info->show();
            ui->info->setText("密码错误");
            ui->password->setText("");
        }
    }
    else{
        ui->info->show();
        ui->info->setText("用户不存在");
    }
    if(isLogin){//登陆成功发射登陆成功信号并清空输入框
        pressCancel();
        emit this->loginSuccess();
    }
}
void dialog_login::pressCancel(){
    ui->username->setText("");
    ui->password->setText("");
    ui->info->hide();
    ui->info->setText("");
    this->reject();//取消登录直接退出
}
