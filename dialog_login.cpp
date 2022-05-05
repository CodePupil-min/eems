#include "dialog_login.h"
#include "ui_dialog_login.h"

dialog_login::dialog_login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dialog_login)
{
    ui->setupUi(this);
    //连接按钮
    connect(ui->login,&QPushButton::clicked,this,&dialog_login::pressLogin);
    connect(ui->cancel,&QPushButton::clicked,this,&dialog_login::pressCancel);
    db=new database();//建立数据库连接操作
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
            ui->info->setText("密码错误");
            ui->password->setText("");
        }
    }
    else{
        ui->info->setText("用户不存在");
    }
    if(isLogin){//登陆成功发射登陆成功信号并清空输入框
        ui->username->setText("");
        ui->password->setText("");
        this->reject();
        emit this->loginSuccess();
    }
}
void dialog_login::pressCancel(){
    this->reject();//取消登录直接退出
}
