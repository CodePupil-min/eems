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
    DB_users.open();
    if(DB_users.tables().size()==0){
        QSqlQuery sql(DB_users);
        //创建带管理员的表
        sql.exec("create table users (username text(255) primary key not null, password text(255) not null, super integer(1) not null);");
        sql.exec("INSERT INTO users VALUES ('root', '12345678',1);");
        //创建环境监测数据表
        sql.exec("CREATE TABLE envdatas (date text(15),time text(10),tem text(5),hum text(5),zd text(5),fc text(5),atm text(5));");
        sql.exec("CREATE TABLE envdatas2 (date text(15),time text(10),tem text(5),hum text(5),zd text(5),fc text(5),atm text(5));");
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

bool database::insertData(QStringList info,int n){
    QDateTime dt=QDateTime::currentDateTime();
    QString date=dt.date().toString("yyyy/MM/dd");
    QString time=dt.time().toString("hh:mm:ss");
    QString tem=info[0];
    QString hum=info[1];
    QString zd=info[2];
    QString fc=info[3];
    QString atm=info[4];
    DB_users.open();
    QSqlQuery sql(DB_users);
    QString sqlstr="INSERT INTO envdatas VALUES ('"+date+"','"+time+"','"+tem+"','"+hum+"','"+zd+"','"+fc+"','"+atm+"')";
    if(n==2)sqlstr="INSERT INTO envdatas2 VALUES ('"+date+"','"+time+"','"+tem+"','"+hum+"','"+zd+"','"+fc+"','"+atm+"')";
//    qDebug()<<sqlstr;
    bool f=sql.exec(sqlstr);
    DB_users.close();
    return f;
}

QVector<QVector<QString>> database::readData(QString date,int n){
    QVector<QVector<QString>>vector;
    DB_users.open();
    QSqlQuery sql(DB_users);
    QString sqlstr="SELECT * from envdatas where date='"+date+"';";
    if(n==2)sqlstr="SELECT * from envdatas2 where date='"+date+"';";
//    qDebug()<<sqlstr;
    sql.exec(sqlstr);
    while(sql.next()){
        QVector<QString>va={sql.value(0).toString(),//date
                            sql.value(1).toString(),//time
                            sql.value(2).toString(),//tem
                            sql.value(3).toString(),//hum
                            sql.value(4).toString(),//zd
                            sql.value(5).toString(),//fc
                            sql.value(6).toString()};//atm
        vector.append(va);
    }
    DB_users.close();
    return vector;
}
QVector<QVector<QString>> database::readData6(QString date,int n){
    QVector<QVector<QString>>vector;
    DB_users.open();
    QSqlQuery sql(DB_users);
    QString sqlstr="SELECT * FROM (select * from envdatas where date='"+date+"' order by time desc limit 6) aa ORDER BY time";
    if(n==2)sqlstr="SELECT * FROM (select * from envdatas2 where date='"+date+"' order by time desc limit 6) aa ORDER BY time";
//    qDebug()<<sqlstr;
    sql.exec(sqlstr);
    while(sql.next()){
        QVector<QString>va={sql.value(0).toString(),//date
                            sql.value(1).toString(),//time
                            sql.value(2).toString(),//tem
                            sql.value(3).toString(),//hum
                            sql.value(4).toString(),//zd
                            sql.value(5).toString(),//fc
                            sql.value(6).toString()};//atm
        vector.append(va);
    }
    DB_users.close();
    return vector;
}
bool database::removeDay(QString date,int n){
    DB_users.open();
    QSqlQuery sql(DB_users);
    QString sqlstr="delete from envdatas where date='"+date+"'";
    if(n==2)sqlstr="delete from envdatas2 where date='"+date+"'";
    bool f=sql.exec(sqlstr);
    DB_users.close();
    return f;
}
