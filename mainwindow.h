#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "page_env.h"
#include "page_dev.h"
#include "page_data.h"
#include "page_net.h"
#include "page_super.h"
#include "dialog_login.h"
#include "confirm.h"
#include "tool.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //各个次级页面选择
    void chooseEnvP();//环境监测页
    void chooseDevP();//设备控制页，仅登录用户可用
    void chooseDataP();//数据管理页
    void chooseNetP();//网络连接页
    void manageUsers();//用户管理页，仅管理员可用
    void setMenuButton();//设置按钮动态样式
    void updateUserStatus();//更新登陆状态
    void pressExit();//退出登录
    void login();//登录窗口
    bool eventFilter(QObject *obj, QEvent *event);//事件过滤器
public slots:
    void loginSuccess();//登陆成功槽函数
private:
    Ui::MainWindow *ui;
    //次级页面指针
    page_env* p_env;
    page_dev* p_dev;
    page_data* p_data;
    page_net* p_net;
    page_super* p_super;
    dialog_login* d_login;
    //登录状态
    bool isLogin=1;
    bool isSuper=1;
    QString username="";

};
#endif // MAINWINDOW_H
