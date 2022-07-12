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
#include "tool.h"
#include "database.h"

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

    void setDeviceUnit();//更新设备状态
    void controlDev();//控制设备信号

    void savedata();//保存数据
    bool isLogin=false;
public slots:
    void getWeatherInfo(QNetworkReply*);//获取天气信息
    void glitter();
private:
    Ui::page_env *ui;
    QFont iconFont;
    database* db;
    QNetworkReply *m_Reply;//天气相关
    QMap<QString,QString>* weathermap;//天气信息
    QSerialPort* currentport=nullptr;
    QStringList env_info;
    bool light=false;
    bool motor=false;
    QTimer* gli;
};

#endif // PAGE_ENV_H
