#ifndef PAGE_SUPER_H
#define PAGE_SUPER_H

#include <QWidget>
#include <QStandardItemModel>
#include<QTimer>
#include "database.h"
#include "confirm.h"
#include "tool.h"
namespace Ui {
class page_super;
}

class page_super : public QWidget
{
    Q_OBJECT

public:
    explicit page_super(QWidget *parent = nullptr);
    ~page_super();
    void updateRecord();//加载数据更新记录
    void addRecord();//添加用户
    void rmRecord();//删除用户
    void pressPwdvis();
    void pressAdduser();
    void pressCanceladd();//取消添加

private:
    Ui::page_super *ui;
    database *db;
    QVector<QVector<QString>>data;
    QStandardItemModel *content;//表格模型
    bool pwdisvisable=false;//密码是否可见
};

#endif // PAGE_SUPER_H
