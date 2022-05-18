#ifndef PAGE_DATA_H
#define PAGE_DATA_H

#include <QWidget>
#include "tool.h"

namespace Ui {
class page_data;
}

class page_data : public QWidget
{
    Q_OBJECT

public:
    explicit page_data(QWidget *parent = nullptr);
    ~page_data();

private:
    Ui::page_data *ui;
    QFont iconFont;
};

#endif // PAGE_DATA_H
