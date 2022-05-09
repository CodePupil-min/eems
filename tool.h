#ifndef TOOL_H
#define TOOL_H
#include <QFontDatabase>

#define _icon_env QChar(0xf06c)//leaf
#define _icon_dev QChar(0xf0e8)//sitemap
#define _icon_data QChar(0xf1c0)//database
#define _icon_net QChar(0xf1eb)//wifi
#define _icon_exit QChar(0xf2f5)//sign-out-alt
#define _icon_user QChar(0xf007)//user
#define _icon_super QChar(0xf4fe)//user-cog
#define _icon_user_plus QChar(0xf234)//user_plus
#define _icon_not_login QChar(0xf2bd)//user-circle
#define _icon_lock QChar(0xf023)//lock
#define _icon_key QChar(0xf084)//key
#define _icon_warn QChar(0xf071)//exclamation-triangle
#define _icon_check QChar(0xf14a)//check_square
#define _icon_eye QChar(0xf06e)//check_eye
#define _icon_eye_slash QChar(0xf070)//check_eye_slash
#define _icon_trash QChar(0xf2ed)//trash-alt
#define _icon_fault QChar(0xf410)//window_close
#define _icon_users QChar(0xf500)//user-friends

class Tool
{
public:
    Tool();
    QFont getIconFont();//获取图表字体
private:
    QFont iconFont;//图标字体
};

#endif // TOOL_H
