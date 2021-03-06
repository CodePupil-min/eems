QT       += core gui
QT       += sql
QT       += network
QT       += serialport
QT       += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    confirm.cpp \
    database.cpp \
    dialog_login.cpp \
    main.cpp \
    mainwindow.cpp \
    page_data.cpp \
    page_dev.cpp \
    page_env.cpp \
    page_net.cpp \
    page_super.cpp \
    tool.cpp

HEADERS += \
    confirm.h \
    database.h \
    dialog_login.h \
    mainwindow.h \
    page_data.h \
    page_dev.h \
    page_env.h \
    page_net.h \
    page_super.h \
    tool.h

FORMS += \
    confirm.ui \
    dialog_login.ui \
    mainwindow.ui \
    page_data.ui \
    page_dev.ui \
    page_env.ui \
    page_net.ui \
    page_super.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    data/source.qrc
