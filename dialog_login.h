#ifndef DIALOG_LOGIN_H
#define DIALOG_LOGIN_H

#include <QDialog>
#include"database.h"
#include "tool.h"

namespace Ui {
class dialog_login;
}

class dialog_login : public QDialog
{
    Q_OBJECT

public:
    explicit dialog_login(QWidget *parent = nullptr);
    ~dialog_login();
    bool isLogin=false;
    bool isSuper=false;
    QString username="";
    void pressLogin();
    void pressCancel();

signals:
    void loginSuccess();//登陆成功信号

private:
    Ui::dialog_login *ui;
    database *db;
};

#endif // DIALOG_LOGIN_H
