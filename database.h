#ifndef DATABASE_H
#define DATABASE_H

#include<QVector>
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDateTime>
#include "tool.h"
class database
{
public:
    database();
    //登录验证相关
    bool isUserExist(QString user);
    bool isPwdTrue(QString pwd);
    bool isSuperUser();
    //用户增删查改
    bool addUser(QString user,QString pwd,bool super=0);//添加用户,添加时注意判断字符串空，判断用户是否存在
    QVector<QVector<QString>> selectAllUsers();//列出所有用户
    bool removeUser(QString user);//删除用户//删除前先判断是否存在
    bool alterPwd(QString user,QString pwd);//修改密码
    //环境信息存储表
    bool insertData(QStringList info,int n);//插入数据
    bool removeDay(QString date,int n);//删除某一天全部数据
    QVector<QVector<QString>> readData(QString date,int n);
    QVector<QVector<QString>> readData10(QString date,int n);

private:

    bool findUser(QString user);//查找用户
    QSqlDatabase DB_users;
    QString username="";
    QString password="";
    bool isSuper=false;
};

#endif // DATABASE_H
