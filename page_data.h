#ifndef PAGE_DATA_H
#define PAGE_DATA_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTimer>
#include "tool.h"
#include "confirm.h"
#include "database.h"

namespace Ui {
class page_data;
}

class page_data : public QWidget
{
    Q_OBJECT

public:
    explicit page_data(QWidget *parent = nullptr);
    ~page_data();

    void updateRecord();//根据日期加载数据更新记录
    void removeRecord();
    bool isLogin=false;
private:
    Ui::page_data *ui;
    QFont iconFont;
    database *db;
    QVector<QVector<QString>>data;
    QStandardItemModel *content;//表格模型
};

#endif // PAGE_DATA_H
