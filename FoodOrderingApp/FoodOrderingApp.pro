QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cart.cpp \
    cartdata.cpp \
    dish.cpp \
    dishlist.cpp \
    homepage.cpp \
    main.cpp \
    payment.cpp \
    restaurant.cpp

HEADERS += \
    Application.h \
    cart.h \
    cartdata.h \
    dish.h \
    dishlist.h \
    homepage.h \
    initdb.h \
    payment.h \
    restaurant.h \
    typedef.h

FORMS += \
    cart.ui \
    dish.ui \
    dishlist.ui \
    homepage.ui \
    payment.ui \
    restaurant.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
