#ifndef PAGE_ENV_H
#define PAGE_ENV_H

#include <QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTimer>
#include <QGraphicsDropShadowEffect>
#include <QtCharts>
#include "tool.h"
#include "database.h"
QT_CHARTS_USE_NAMESPACE
namespace Ui {
class page_env;
}

class page_env : public QWidget
{
    Q_OBJECT
public:
    explicit page_env(QWidget *parent = nullptr);
    ~page_env();
    //天气模块相关
    void setWeatherUnit();//设置天气部分ui
    void updateWeather();//更新天气
    void updateTime();//刷新时间
    //串口通信相关
    void setCurrentPort(QSerialPort** port);//设置已实例化的串口类
    void updateSerPortInfo();//接受数据并更新
    void setMonitorUnit();//更新环境数据
    //监控模块相关
    void setDeviceUnit();//更新设备状态
    void controlDev();//控制设备信号
    void controlDev2();//控制设备信号
    void savedata();//保存数据

    bool isLogin=false;
    QStringList env_info;
    QStringList env_info2;
public slots:
    void getWeatherInfo(QNetworkReply*);//获取天气信息
    void glitter();
    void glitter2();
    void lossLongTime();//超时所有数据均变为0
private:
    Ui::page_env *ui;
    QFont iconFont;
    database* db;
    QNetworkReply *m_Reply;//天气相关
    QMap<QString,QString>* weathermap;//天气信息
    QSerialPort* currentport=nullptr;
    QString portinfo="";
    bool light=0;
    bool motor=0;
    bool light_2=0;
    bool motor_2=0;
    QTimer* gli;
    QTimer* gli2;
    QTimer* timelimit;
};

#endif // PAGE_ENV_H
