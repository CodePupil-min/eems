#include "database.h"

database::database()
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
        DB_users = QSqlDatabase::database("qt_sql_default_connection");
    else{
        DB_users=QSqlDatabase::addDatabase("QSQLITE");
        DB_users.setDatabaseName("datas.db");
    }
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

bool database::addUser(QString user, QString pwd){
    if(user==""||pwd=="")return false;//空
    DB_users.open();
    QSqlQuery sql(DB_users);
    QString sqlstr="INSERT INTO users VALUES ('"+user+"', '"+pwd+"',0)";
    bool f=sql.exec(sqlstr);
    DB_users.close();
    return f;
}
QVector<QVector<QString>> database::selectAllUsers(){
    QVector<QVector<QString>>vector;
    DB_users.open();
    QSqlQuery sql(DB_users);
    QString sqlstr="SELECT username,password from users where super is 0";
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
    return removeUser(user)&&addUser(user,pwd);
}
