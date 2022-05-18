#ifndef PAGE_ENV_H
#define PAGE_ENV_H

#include <QWidget>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QTimer>
#include "tool.h"

namespace Ui {
class page_env;
}

class page_env : public QWidget
{
    Q_OBJECT
public:
    explicit page_env(QWidget *parent = nullptr);
    ~page_env();
    void setWeatherUnit();//设置天气部分ui
    void updateWeather();//更新天气
    void updateTime();
public slots:
    void getWeatherInfo(QNetworkReply*);//获取天气信息
private:
    Ui::page_env *ui;
    QFont iconFont;
    QNetworkReply *m_Reply;//天气相关
    QMap<QString,QString>* weathermap;//天气信息

};

#endif // PAGE_ENV_H
