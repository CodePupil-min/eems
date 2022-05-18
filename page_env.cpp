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
    weathermap=new QMap<QString,QString>();
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
    QJsonObject info_json = jsonDocument.object();
    QJsonObject data=info_json.value("data").toObject();//数据
    QJsonObject today_weather=data.value("forecast")[0].toObject();//当日天气
    //获取内容
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
//    for(auto it = weathermap->begin();it!=weathermap->end();it++)
//    {
//        qDebug()<<it.key()<<it.value();
//    }
    setWeatherUnit();//ui显示
    m_Reply->deleteLater();//释放内存
}

void page_env::setWeatherUnit(){
    //天气
    QString t=weathermap->value("type");
//    t="多云";//debug
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
    }else if(t=="多云"){
        ui->type_icon->setText(_icon_cloud_sun);
        ui->img->setStyleSheet("#img{border-image: url(:/image/cloudy.png);}");
    }else{//其他待补充
        ui->type_icon->setText(_icon_other);
        ui->img->setStyleSheet("#img{border-image: url(:/image/other.png);}");
    }
    //温度
    ui->tem->setText(weathermap->value("tem"));
    ui->tem_hl->setText("H:"+weathermap->value("tem_h")+"\nL:"+weathermap->value("tem_l"));
    //空气质量
    ui->quality->setText(weathermap->value("quality"));
    //pm10\pm2.5
    ui->pm->setText("PM2.5:"+weathermap->value("pm25")+"\nPM 10:"+weathermap->value("pm10"));
    //位置
    ui->local->setFont(iconFont);
    ui->local->setText("户外环境: "+QString(_icon_local)+"北京市");
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
