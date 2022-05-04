#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFontDatabase>
#include "page_env.h"
#include "page_dev.h"
#include "page_data.h"
#include "page_net.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //各个次级页面选择
    void chooseEnvP();
    void chooseDevP();
    void chooseDataP();
    void chooseNetP();
    void setMenuButton();
    bool eventFilter(QObject *obj, QEvent *event);

private:
    Ui::MainWindow *ui;
    //次级页面指针
    page_env* p_env;
    page_dev* p_dev;
    page_data* p_data;
    page_net* p_net;
    //图标
    QFont iconFont;
};
#endif // MAINWINDOW_H
