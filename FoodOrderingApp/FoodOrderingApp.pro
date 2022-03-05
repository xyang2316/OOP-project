QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cart.cpp \
    dish.cpp \
    dishlist.cpp \
    main.cpp \
    payment.cpp \
    restaurant.cpp

HEADERS += \
    cart.h \
    dish.h \
    dishlist.h \
    global.h \
    initdb.h \
    payment.h \
    restaurant.h

FORMS += \
    cart.ui \
    dish.ui \
    dishlist.ui \
    payment.ui \
    restaurant.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
