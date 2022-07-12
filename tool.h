#ifndef TOOL_H
#define TOOL_H
#include <QFontDatabase>
#include <QDebug>

//目录
#define _icon_env QChar(0xf06c)//leaf
#define _icon_dev QChar(0xf0e8)//sitemap
#define _icon_data QChar(0xf1c0)//database
#define _icon_net QChar(0xf1eb)//wifi
#define _icon_exit QChar(0xf2f5)//sign-out-alt

#define _icon_lock QChar(0xf023)//lock
#define _icon_key QChar(0xf084)//key
#define _icon_warn QChar(0xf071)//exclamation-triangle
#define _icon_check QChar(0xf14a)//check_square
#define _icon_eye QChar(0xf06e)//check_eye
#define _icon_eye_slash QChar(0xf070)//check_eye_slash
#define _icon_trash QChar(0xf2ed)//trash-alt
#define _icon_fault QChar(0xf410)//window_close
//用户相关
#define _icon_user QChar(0xf007)//user
#define _icon_super QChar(0xf4fe)//user-cog
#define _icon_user_plus QChar(0xf234)//user_plus
#define _icon_not_login QChar(0xf2bd)//user-circle
#define _icon_users QChar(0xf500)//user-friends
//天气相关
#define _icon_cloud_sun QChar(0xf6c4)//cloud-sun
#define _icon_cloud QChar(0xf0c2)//cloud
#define _icon_sun QChar(0xf185)//sun
#define _icon_rain QChar(0xf73d)//cloud-rain

#define _icon_local QChar(0xf3c5)//map-marker-alt
#define _icon_other QChar(0xf118)//smile
#define _icon_haze QChar(0xf534)//infinity
#define _icon_snow QChar(0xf2dc)//snow
#define _icon_refresh QChar(0xf01e)//redo

#define _icon_tem QChar(0xf2c9)//tem
#define _icon_hum QChar(0xf46a)//hum
#define _icon_zd QChar(0xf042)//照度
#define _icon_fc QChar(0xf604)//lung
#define _icon_atm QChar(0xf1ce)//atm

#define _icon_light QChar(0xf0eb)//light
#define _icon_fan QChar(0xf863)//fan

#define node_num 5//节点数
#define savetime 5000

class Tool
{
public:
    Tool();
    QFont getIconFont();//获取图表字体
private:
    QFont iconFont;//图标字体
};

#endif // TOOL_H
