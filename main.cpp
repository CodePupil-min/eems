#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("嵌入式环境监测系统");
    w.setWindowIcon(QIcon(":/image/leaf.jpg"));
    w.show();
    return a.exec();
}
