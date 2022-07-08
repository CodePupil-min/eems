#ifndef PAGE_DEV_H
#define PAGE_DEV_H

#include <QWidget>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "tool.h"

namespace Ui {
class page_dev;
}

class page_dev : public QWidget
{
    Q_OBJECT

public:
    explicit page_dev(QWidget *parent = nullptr);
    ~page_dev();
    void setTitle(bool isLogin=false);
     //串口通信相关
    void setCurrentPort(QSerialPort** port);//设置已实例化的串口类
    void sendPortMsg();
    bool isLogin=false;
private:
    Ui::page_dev *ui;
    QFont iconFont;
    QSerialPort* currentport=nullptr;
};

#endif // PAGE_DEV_H
