#include "page_env.h"
#include "ui_page_env.h"

page_env::page_env(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page_env)
{
    ui->setupUi(this);
    //一些初始的ui
    iconFont=(new Tool())->getIconFont();
    ui->logo->setFont(iconFont);
    ui->logo->setText(_icon_env);
    ui->icon_s_tem->setFont(iconFont);
    ui->icon_s_tem->setText(_icon_tem);
    ui->icon_s_hum->setFont(iconFont);
    ui->icon_s_hum->setText(_icon_hum);
    ui->icon_s_zd->setFont(iconFont);
    ui->icon_s_zd->setText(_icon_zd);
    ui->icon_s_fc->setFont(iconFont);
    ui->icon_s_fc->setText(_icon_fc);
    ui->icon_s_atm->setFont(iconFont);
    ui->icon_s_atm->setText(_icon_atm);
    ui->icon_s_tem_2->setFont(iconFont);
    ui->icon_s_tem_2->setText(_icon_tem);
    ui->icon_s_hum_2->setFont(iconFont);
    ui->icon_s_hum_2->setText(_icon_hum);
    ui->icon_s_zd_2->setFont(iconFont);
    ui->icon_s_zd_2->setText(_icon_zd);
    ui->icon_s_fc_2->setFont(iconFont);
    ui->icon_s_fc_2->setText(_icon_fc);
    ui->icon_s_atm_2->setFont(iconFont);
    ui->icon_s_atm_2->setText(_icon_atm);

    ui->light->setFont(iconFont);
    ui->light->setText(_icon_light);
    ui->motor->setFont(iconFont);
    ui->motor->setText(_icon_fan);
    ui->light_2->setFont(iconFont);
    ui->light_2->setText(_icon_light);
    ui->motor_2->setFont(iconFont);
    ui->motor_2->setText(_icon_fan);

    weathermap=new QMap<QString,QString>();
    db=new database();
    //初始化环境信息
    QString nodes="0,0,0,0,0,0,00";//温度，湿度，照度，粉尘浓度，大气压强，序号，设备状态
    env_info=nodes.split(",");
    env_info2=nodes.split(",");
    //更新系统时间
    updateTime();
    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&page_env::updateTime);
    timer->start(1000);//一秒一次
    //更新天气
    updateWeather();
    QTimer *timer1 = new QTimer(this);
    connect(timer1,&QTimer::timeout,this,&page_env::updateWeather);
    timer1->start(600000);//十分钟一次
    //保存数据
    QTimer *timer2 = new QTimer(this);
    connect(timer2,&QTimer::timeout,this,&page_env::savedata);
    timer2->start(savetime);//十秒一次（暂定）
    //超时时间
    timelimit = new QTimer(this);
    connect(timelimit,&QTimer::timeout,this,&page_env::lossLongTime);
    //报警灯
    gli=new QTimer(this);
    connect(gli,&QTimer::timeout,this,&page_env::glitter);
    //报警灯2
    gli2=new QTimer(this);
    connect(gli2,&QTimer::timeout,this,&page_env::glitter2);
    //设备控制按钮
    QPushButton* btn[]={ui->motor,ui->motor_2,ui->light,ui->light_2};
    for(int i=0;i<4;i++){
        QGraphicsDropShadowEffect *shadow=new QGraphicsDropShadowEffect(this);
        shadow->setOffset(0,0);
        shadow->setColor("#c7c7c7");
        shadow->setBlurRadius(30);
        btn[i]->setGraphicsEffect(shadow);
    }
    connect(ui->light,&QPushButton::clicked,this,&page_env::controlDev);
    connect(ui->motor,&QPushButton::clicked,this,&page_env::controlDev);
    connect(ui->light_2,&QPushButton::clicked,this,&page_env::controlDev2);
    connect(ui->motor_2,&QPushButton::clicked,this,&page_env::controlDev2);
}

page_env::~page_env()
{
    delete ui;
}

void page_env::updateWeather(){
    QNetworkAccessManager* m_NetManger = new QNetworkAccessManager();
    QUrl url("http://t.weather.sojson.com/api/weather/city/101010100");
    m_Reply=m_NetManger->get(QNetworkRequest(url));  //发送请求
    connect(m_NetManger, SIGNAL(finished(QNetworkReply*)),this, SLOT(getWeatherInfo(QNetworkReply*)));  //响应结束后发送finished信号，执行对应槽函数
}

void page_env::getWeatherInfo(QNetworkReply*){
    m_Reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    m_Reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    if (m_Reply->error() != QNetworkReply::NoError){
        qDebug()<< m_Reply->errorString();
        return;
    }
    QString info_string = QString::fromUtf8(m_Reply->readAll());//获取到的数据
    //    json解析
    QJsonDocument jsonDocument = QJsonDocument::fromJson(info_string.toUtf8().data());
    if( jsonDocument.isNull() ){
        qDebug()<<"字符串错误";
        return;
    }
    //获取内容
    QJsonObject info_json = jsonDocument.object();
    QJsonObject data=info_json.value("data").toObject();//数据
    QJsonObject today_weather=data.value("forecast")[0].toObject();//当日天气
    //封装
    weathermap->insert("updatetime",info_json.value("time").toString().replace(0,11,""));//更新时间
    weathermap->insert("pm10",QString::number(data.value("pm10").toInt()));//pm10
    weathermap->insert("pm25",QString::number(data.value("pm25").toInt()));//pm2.5
    weathermap->insert("quality",data.value("quality").toString());//空气质量
    weathermap->insert("humid",data.value("shidu").toString());//湿度
    weathermap->insert("tem",data.value("wendu").toString()+"℃");//温度
    weathermap->insert("type",today_weather.value("type").toString());//天气
    weathermap->insert("tem_h",today_weather.value("high").toString().replace("高温 ",""));//最高温
    weathermap->insert("tem_l",today_weather.value("low").toString().replace("低温 ",""));//最低温
    weathermap->insert("notice",today_weather.value("notice").toString());//建议
    setWeatherUnit();//ui显示
    m_Reply->deleteLater();//释放内存
}

void page_env::setWeatherUnit(){
    //天气
    QString t=weathermap->value("type");
//    t="大雪";//debug
    ui->type_icon->setFont(iconFont);
    ui->type->setText(t);
    //天气情况
    if(t.contains("晴")){
        ui->type_icon->setText(_icon_sun);
        ui->type_icon->setStyleSheet(ui->type_icon->styleSheet()+"color:yellow");
        ui->img->setStyleSheet("#img{border-image: url(:/image/sunny.png);}");
    }else if(t.contains("雨")){
        ui->type_icon->setText(_icon_rain);
        ui->img->setStyleSheet("#img{border-image: url(:/image/rain.png);}");
    }else if(t.contains("阴")){
        ui->type_icon->setText(_icon_cloud);
        ui->img->setStyleSheet("#img{border-image: url(:/image/overcast.png);}");
    }else if(t.contains("多云")){
        ui->type_icon->setText(_icon_cloud_sun);
        ui->img->setStyleSheet("#img{border-image: url(:/image/cloudy.png);}");
    }else if(t.contains("雪")){
        ui->type_icon->setText(_icon_snow);
        ui->img->setStyleSheet("#img{border-image: url(:/image/snow.png);}");
    }else if(t.contains("霾")){
        ui->type_icon->setText(_icon_haze);
        ui->img->setStyleSheet("#img{border-image: url(:/image/haze.png);}");
    }else{//其他待补充
        ui->type_icon->setText(_icon_other);
        ui->img->setStyleSheet("#img{border-image: url(:/image/other.png);}");
    }
    //温度
    ui->tem->setText(weathermap->value("tem"));
    ui->tem_hl->setText("H:"+weathermap->value("tem_h")+"\nL:"+weathermap->value("tem_l"));
    //空气质量
    ui->quality->setText(weathermap->value("quality").at(0));
    //pm10\pm2.5
    ui->pm->setText("PM2.5:"+weathermap->value("pm25")+"\nPM 10:"+weathermap->value("pm10"));
    //位置
    ui->local->setFont(iconFont);
    ui->local->setText("户外环境: "+QString(_icon_local)+" 北京市");
    //notice
    ui->notice->setText(weathermap->value("notice"));
}

void page_env::updateTime(){
    QDateTime systime = QDateTime::currentDateTime();
    QString time = systime.toString("hh:mm");
    QString date = systime.toString("yyyy-MM-dd");
    QString week = systime.toString("dddd");
    ui->sys_time->setText(time);
    ui->sys_date->setText(date);
    ui->sys_week->setText(week);
}

void page_env::setCurrentPort(QSerialPort** port){
    currentport=*port;
    connect(currentport,&QSerialPort::readyRead,this,&page_env::updateSerPortInfo);//连接串口，获取到之后执行
}

void page_env::updateSerPortInfo(){//包括设备状态
    if(currentport==nullptr)return;
    QString s = currentport->readAll();
    portinfo+=s;
    if(s.back()!='\n')return;
    timelimit->stop();
    timelimit->start(losstime);//30s超时
    s=portinfo.replace("\r\n","");
    portinfo="";
    QStringList info=s.split(",");
    //温度，湿度，照度，粉尘浓度，大气压强，序号，设备状态
    if(info.length()<node_num+2)return;//数据无效
    ui->hint->hide();
    int n=info[5].toInt();
    if(!(n==1||n==2))return;
    n==1?env_info=info:env_info2=info;
    setMonitorUnit();//更新数据
    int devc_ml=info[info.length()-1].toInt();
    if(devc_ml!=0&&devc_ml!=1&&devc_ml!=10&&devc_ml!=11)return;
    if(n==1){
        motor=devc_ml/10;light=devc_ml%10;
    }
    else{
        motor_2=devc_ml/10;light_2=devc_ml%10;
    }
    setDeviceUnit();//按钮状态
}
void page_env::lossLongTime(){
    timelimit->stop();
    QString nodes="0,0,0,0,0,0,00";//温度，湿度，照度，粉尘浓度，大气压强，序号，设备状态
    env_info=nodes.split(",");
    env_info2=nodes.split(",");
    setMonitorUnit();
    ui->hint->show();
}
void page_env::glitter(){
    QString on="background-color:red";
    QString off="background-color:#c7c7c7";
    if(!QString::compare(ui->alarm->styleSheet(),on))ui->alarm->setStyleSheet(off);
    else ui->alarm->setStyleSheet(on);
}
void page_env::glitter2(){
    QString on="background-color:red";
    QString off="background-color:#c7c7c7";
    if(!QString::compare(ui->alarm_2->styleSheet(),on))ui->alarm_2->setStyleSheet(off);
    else ui->alarm_2->setStyleSheet(on);
}
void page_env::setMonitorUnit(){
    QLabel* labels[]={ui->s_tem,ui->s_hum,ui->s_zd,ui->s_fc,ui->s_atm};
    QLabel* labels2[]={ui->s_tem_2,ui->s_hum_2,ui->s_zd_2,ui->s_fc_2,ui->s_atm_2};
    QString dws[]={" ℃"," %RH",""," pcs/283ml"," Kpa"};
    QString zd[]={"暗","较暗","适宜","较亮","亮"};
    //温度临界值
    if(env_info[0].toFloat()>35) ui->s_tem->setStyleSheet("color:red;");
    else ui->s_tem->setStyleSheet("color:green;");
    //2
    if(env_info2[0].toFloat()>35) ui->s_tem_2->setStyleSheet("color:red;");
    else ui->s_tem_2->setStyleSheet("color:green;");
    //湿度
    if(env_info[1].toFloat()>=45&&env_info[1].toFloat()<=65)ui->s_hum->setStyleSheet("color:green");
    else ui->s_hum->setStyleSheet("color:white");
    //2
    if(env_info2[1].toFloat()>=45&&env_info2[1].toFloat()<=65)ui->s_hum_2->setStyleSheet("color:green");
    else ui->s_hum_2->setStyleSheet("color:white");
    //粉尘报警
    if(env_info[3].toFloat()>6000){if(!gli->isActive())gli->start(500);ui->s_fc->setStyleSheet("color:red;");}
    else{
        gli->stop();
        ui->alarm->setStyleSheet("background-color:#c7c7c7");
        ui->s_fc->setStyleSheet("color:white;");
    }
    //2
    if(env_info2[3].toFloat()>6000){if(!gli2->isActive())gli2->start(500);ui->s_fc_2->setStyleSheet("color:red;");}
    else{
        gli2->stop();
        ui->alarm_2->setStyleSheet("background-color:#c7c7c7");
        ui->s_fc_2->setStyleSheet("color:white;");
    }
    //填写数据
    for(int i=0;i<node_num;i++){
        labels[i]->setText(env_info[i]+dws[i]);
        labels2[i]->setText(env_info2[i]+dws[i]);
    }
    int z=ui->s_zd->text().toInt();
    if(z>=1&&z<=5)ui->s_zd->setText(zd[z-1]);
    else ui->s_zd->setText("未知");
    if(z==3)ui->s_zd->setStyleSheet("color:green");
    else ui->s_zd->setStyleSheet("color:white");
    //2
    int z2=ui->s_zd_2->text().toInt();
    if(z2>=1&&z2<=5)ui->s_zd_2->setText(zd[z2-1]);
    else ui->s_zd_2->setText("未知");
    if(z2==3)ui->s_zd_2->setStyleSheet("color:green");
    else ui->s_zd_2->setStyleSheet("color:white");
}

void page_env::setDeviceUnit(){
    //根据登录状态判断是否启用按钮
    QString disable="background-color:#c7c7c7;color:white;border:2px solid #c7c7c7;";
    ui->light->setEnabled(isLogin);
    ui->motor->setEnabled(isLogin);
    ui->light_2->setEnabled(isLogin);
    ui->motor_2->setEnabled(isLogin);
    if(!isLogin){
        ui->light->setStyleSheet(disable);
        ui->motor->setStyleSheet(disable);
        ui->light_2->setStyleSheet(disable);
        ui->motor_2->setStyleSheet(disable);
        return;
    }
    QString off="background-color:white;color:#7EABFF;border:2px solid #7EABFF;";
    QString on="background-color:#7EABFF;color:white;border:2px solid white;";
    if(light)ui->light->setStyleSheet(on);
    else ui->light->setStyleSheet(off);
    if(motor)ui->motor->setStyleSheet(on);
    else ui->motor->setStyleSheet(off);
    if(light_2)ui->light_2->setStyleSheet(on);
    else ui->light_2->setStyleSheet(off);
    if(motor_2)ui->motor_2->setStyleSheet(on);
    else ui->motor_2->setStyleSheet(off);
}
void page_env::controlDev(){
    QString btnname=QObject::sender()->objectName();
    QString::compare(btnname,ui->light->objectName())?motor=!motor:light=!light;
    QString s=QString::number(motor*2+light);
    setDeviceUnit();//改变按钮状态
    currentport->write(s.toLocal8Bit());
}
void page_env::controlDev2(){
    QString btnname=QObject::sender()->objectName();
    QString::compare(btnname,ui->light_2->objectName())?motor_2=!motor_2:light_2=!light_2;
    QString s=QString::number(4+motor_2*2+light_2);
    setDeviceUnit();//改变按钮状态
    currentport->write(s.toLocal8Bit());
}
void page_env::savedata(){
    if(!isLogin)return;//未登录
    if(QString::compare(env_info[5],"0"))
        db->insertData(env_info,1);//登录状态下存储数据
    if(QString::compare(env_info2[5],"0"))
        db->insertData(env_info2,2);//登录状态下存储数据
}
