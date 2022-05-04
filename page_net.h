#ifndef PAGE_NET_H
#define PAGE_NET_H

#include <QWidget>

namespace Ui {
class page_net;
}

class page_net : public QWidget
{
    Q_OBJECT

public:
    explicit page_net(QWidget *parent = nullptr);
    ~page_net();

private:
    Ui::page_net *ui;
};

#endif // PAGE_NET_H
