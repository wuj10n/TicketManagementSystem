QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    manage.cpp \
    order.cpp \
    client.cpp \
    globle.cpp \
    db.cpp

HEADERS += \
    mainwindow.h \
    manage.h \
    order.h \
    client.h \
    globle.h

FORMS += \
    mainwindow.ui \
    manage.ui \
    order.ui \
    client.ui

TRANSLATIONS += \
    TicketManagementSystem_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
