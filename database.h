#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <qdebug.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
class database
{
public:
    database();
    //登录验证相关
    bool isUserExist(QString user);
    bool isPwdTrue(QString pwd);
    bool isSuperUser();
    //用户增删查改
    //环境信息存储表

private:
    bool findUser(QString user);//查找用户
    QSqlDatabase DB_users;
    QString username="";
    QString password="";
    bool isSuper=false;
};

#endif // DATABASE_H
