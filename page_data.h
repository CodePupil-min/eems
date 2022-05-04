#ifndef PAGE_DATA_H
#define PAGE_DATA_H

#include <QWidget>

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
};

#endif // PAGE_DATA_H
