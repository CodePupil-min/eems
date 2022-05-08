#include "database.h"

database::database()
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        DB_users = QSqlDatabase::database("qt_sql_default_connection");
    else{
        DB_users=QSqlDatabase::addDatabase("QSQLITE");
        DB_users.setDatabaseName("datas.db");
    }
    //第一次运行,数据库不存在，系统自动新建数据库
    //创建带管理员的表
    DB_users.open();
    if(DB_users.tables().size()==0){
        QSqlQuery sql(DB_users);
        sql.exec("create table users (username text(255) primary key not null, password text(255) not null, super integer(1) not null);");
        sql.exec("INSERT INTO users VALUES ('root', '12345678',1);");
    }
    DB_users.close();
}

bool database::findUser(QString user){
    username="";
    password="";
    isSuper=false;
    DB_users.open();
    QSqlQuery sql(DB_users);
    QString sqlstr="select * from users where username='"+user+"'";
    sql.exec(sqlstr);
    DB_users.close();
    if(sql.next()){
        username=sql.value(0).toString();
        password=sql.value(1).toString();
        isSuper=sql.value(2).toInt();
    }
    if(username!="")
        return true;
    return false;
}
bool database::isUserExist(QString user){
    if(findUser(user))return true;
    return false;
}
bool database::isPwdTrue(QString pwd){
    if(pwd==password)return true;
    return false;
}
bool database::isSuperUser(){
    return isSuper;
}

bool database::addUser(QString user, QString pwd,bool super){
    if(user==""||pwd=="")return false;//空
    DB_users.open();
    QSqlQuery sql(DB_users);
    QString sqlstr="INSERT INTO users VALUES ('"+user+"','"+pwd+"',"+QChar(super?'1':'0')+")";
    bool f=sql.exec(sqlstr);
    DB_users.close();
    return f;
}
QVector<QVector<QString>> database::selectAllUsers(){
    QVector<QVector<QString>>vector;
    DB_users.open();
    QSqlQuery sql(DB_users);
    QString sqlstr="SELECT username,password from users;";
    sql.exec(sqlstr);
    while(sql.next()){
        QVector<QString>va={sql.value(0).toString(),sql.value(1).toString()};
        vector.append(va);
    }
    DB_users.close();
    return vector;
}
bool database::removeUser(QString user){
    DB_users.open();
    QSqlQuery sql(DB_users);
    QString sqlstr="delete from users where username='"+user+"'";
    bool f=sql.exec(sqlstr);
    DB_users.close();
    return f;
}
bool database::alterPwd(QString user,QString pwd){
    DB_users.open();
    QSqlQuery sql(DB_users);
    QString sqlstr="UPDATE users SET password='"+pwd+"' WHERE username='"+user+"'";
    bool f=sql.exec(sqlstr);
    DB_users.close();
    return f;
}
