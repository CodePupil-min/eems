#ifndef PAGE_DEV_H
#define PAGE_DEV_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QtCharts>
#include "tool.h"
#include "database.h"

namespace Ui {
class page_dev;
}

class page_dev : public QWidget
{
    Q_OBJECT

public:
    explicit page_dev(QWidget *parent = nullptr);
    ~page_dev();

    void initChart();
    void updateChart();
    void getData();//从数据库中取6条数据更新
    void updateData();//实时更新
    void chooseUnit();//选择显示的表
    bool isLogin=false;
    QStringList env_info;
    QStringList env_info2;
private:
    Ui::page_dev *ui;
    QFont iconFont;
    database *db;
    QVector<QVector<float>>datas;
    QVector<QString>time;
    QVector<QString>time2;
    QChart *chart[8];
    QLineSeries *series[8];
    QValueAxis *axisY[8];
    QBarCategoryAxis *axisX[8];
    QChartView* views[8];
};

#endif // PAGE_DEV_H
