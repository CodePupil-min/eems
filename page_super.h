#ifndef PAGE_SUPER_H
#define PAGE_SUPER_H

#include <QWidget>

namespace Ui {
class page_super;
}

class page_super : public QWidget
{
    Q_OBJECT

public:
    explicit page_super(QWidget *parent = nullptr);
    ~page_super();

private:
    Ui::page_super *ui;
};

#endif // PAGE_SUPER_H
