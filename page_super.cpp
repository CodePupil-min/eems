#include "page_super.h"
#include "ui_page_super.h"

page_super::page_super(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page_super)
{
    ui->setupUi(this);
    //加载记录
    db=new database();
    updateRecord();
    //隐藏添加用户界面
    ui->addwidget->hide();
    connect(ui->pwdvisbtn,&QPushButton::clicked,this,&page_super::pressPwdvis);
    connect(ui->adduserbtn,&QPushButton::clicked,this,&page_super::pressAdduser);
    connect(ui->sureadd,&QPushButton::clicked,this,&page_super::addRecord);
    connect(ui->canceladd,&QPushButton::clicked,this,&page_super::pressCanceladd);
    connect(ui->rmuserbtn,&QPushButton::clicked,this,&page_super::rmRecord);
    //一些初始的ui
    QFont iconFont=(new Tool())->getIconFont();
    ui->pwdvisbtn->setFont(iconFont);
    ui->pwdvisbtn->setText(pwdisvisable?_icon_eye_slash:_icon_eye);
    ui->logo->setFont(iconFont);
    ui->logo->setText(_icon_users);

}

page_super::~page_super()
{
    delete ui;
}
void page_super::updateRecord(){
    data=db->selectAllUsers();
    content=new QStandardItemModel();
    //添加表头
    content->setColumnCount(3);
    content->setHeaderData(0,Qt::Horizontal,QStringLiteral("序号"));   //设置表头内容
    content->setHeaderData(1,Qt::Horizontal,QStringLiteral("用户名"));
    content->setHeaderData(2,Qt::Horizontal,QStringLiteral("密码"));
    ui->usertable->setModel(content);    //挂载表格模型
    ui->usertable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);        //表头信息显示居中
    ui->usertable->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);  //设定第一列表头列宽不可变
    ui->usertable->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);//设定第2列表头弹性拉伸
    ui->usertable->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Stretch);//设定第3列表头弹性拉伸
    ui->usertable->setColumnWidth(0,80);       //设定表格第1列宽度
    ui->usertable->verticalHeader()->hide();    //隐藏默认显示的行头
    for(int i=0;i<data.size();i++){
        QStandardItem *item0 = new QStandardItem(tr("%1").arg(i+1));
        QString n=data.at(i)[0];
        QStandardItem *item1 = new QStandardItem(n=="root"?n+"(管理员)":n);
        QString pwdstr=pwdisvisable?data.at(i)[1]:"*********";//是否显示密码
        QStandardItem *item2 = new QStandardItem(pwdstr);
        content->setItem(i,0,item0);                                //表格第i行，第1列添加一项内容
        content->setItem(i,1,item1);                                //表格第i行，第2列添加一项内容
        content->setItem(i,2,item2);                                //表格第i行，第3列添加一项内容
        content->item(i,0)->setTextAlignment(Qt::AlignCenter);           //设置表格内容居中
        content->item(i,1)->setTextAlignment(Qt::AlignCenter);           //设置表格内容居中
        content->item(i,2)->setTextAlignment(Qt::AlignCenter);           //设置表格内容居中
    }
}
void page_super::addRecord(){
    QString user=ui->user->text();
    QString pwd=ui->pwd->text();
    QString rpwd=ui->rpwd->text();
    //空或者两次密码不一样直接退出
    if(user==""||pwd==""||rpwd==""||pwd!=rpwd){
        QString style="background:red;";
        if(user=="")ui->user->setStyleSheet(style);
        if(pwd=="")ui->pwd->setStyleSheet(style);
        if(rpwd=="")ui->rpwd->setStyleSheet(style);
        if(pwd!=rpwd){
            ui->pwd->setStyleSheet(style);
            ui->rpwd->setStyleSheet(style);
        }
        QTimer::singleShot(1000, [this]() {
            QString style="background:white;color:black;";
            ui->user->setStyleSheet(style);
            ui->pwd->setStyleSheet(style);
            ui->rpwd->setStyleSheet(style);
        });//恢复输入框
        return;
    }
    if(db->isUserExist(user)){
        confirm *c=new confirm(this);
        if(!c->reveal("用户“"+user+"”已存在，是否修改密码",_icon_warn)){delete c;return;}//取消
        db->alterPwd(user,pwd);//确认修改
    }else{
        confirm *c=new confirm(this);
        if(!c->reveal("添加新用户“"+user+"”",_icon_user_plus)){delete c;return;}//取消
        db->addUser(user,pwd);//确认添加
    }
    confirm *c=new confirm(this);
    if(!c->reveal("操作成功",_icon_check,true)){delete c;return;}//取消
    updateRecord();
    pressCanceladd();
}
void page_super::rmRecord(){
    int row = ui->usertable->selectionModel()->currentIndex().row();//获取选中行行号
    ui->usertable->selectionModel()->clear();//清除选中的效果
    if(row==0){
        confirm *c=new confirm(this);
        c->reveal("不能删除管理员",_icon_fault,true);
        delete c;
        return;
    }//第一行管理员不能删
    if(row==-1){//并未选择任何行
        confirm *c=new confirm(this);
        c->reveal("请选中要删除的用户",_icon_fault,true);
        delete c;
        return;
    }
    QString user = content->item(row,1)->text();//获取选中的用户名
    confirm *c=new confirm(this);
    if(!c->reveal("删除用户“"+user+"”",_icon_trash)){delete c;return;}
    db->removeUser(user);
    updateRecord();
}
void page_super::pressCanceladd(){
    ui->user->setText("");
    ui->pwd->setText("");
    ui->rpwd->setText("");
    ui->addwidget->hide();
}
void page_super::pressAdduser(){
    ui->addwidget->show();
}
void page_super::pressPwdvis(){
    pwdisvisable=!pwdisvisable;
    ui->pwdvisbtn->setText(pwdisvisable?_icon_eye_slash:_icon_eye);
    updateRecord();
}
