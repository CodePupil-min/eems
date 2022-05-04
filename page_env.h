#ifndef PAGE_ENV_H
#define PAGE_ENV_H

#include <QWidget>

namespace Ui {
class page_env;
}

class page_env : public QWidget
{
    Q_OBJECT

public:
    explicit page_env(QWidget *parent = nullptr);
    ~page_env();

private:
    Ui::page_env *ui;
};

#endif // PAGE_ENV_H
