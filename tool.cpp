#include "tool.h"

Tool::Tool(){
    /*设置图标字体*/
    int fontId = QFontDatabase::addApplicationFont(":/font/fa-solid-900.ttf"); //加入字体，并获取字体ID
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0); //获取字体名称
    iconFont = QFont(fontName);
}
QFont Tool::getIconFont(){
    return iconFont;
}
