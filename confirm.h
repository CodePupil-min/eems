#ifndef CONFIRM_H
#define CONFIRM_H

#include <QDialog>
#include "tool.h"
namespace Ui {
class confirm;
}

class confirm : public QDialog
{
    Q_OBJECT

public:
    explicit confirm(QWidget *parent = nullptr);
    ~confirm();
    void pressOK();
    void pressNOK();
    bool reveal(QString message,QChar title=QChar(0),bool onebtn=false);

private:
    Ui::confirm *ui;
};

#endif // CONFIRM_H
