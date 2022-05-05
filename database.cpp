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
    DB_users.tables().size();
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
