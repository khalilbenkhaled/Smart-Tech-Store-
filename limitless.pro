QT += core gui widgets
QT += printsupport
QT       += core gui
QT       += core gui sql
QT += core gui network
QT       += charts serialport multimedia multimediawidgets  widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = smtp
CONFIG += c++11
QT       += core gui sql \
    quick
QT += widgets quickwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += widgets charts
TARGET = QT-Test
TEMPLATE = app
QT += serialport
QT += core gui location qml quickwidgets
QT +=charts



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += core gui





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
    arduino.cpp \
    client.cpp \
    commande.cpp \
    connection.cpp \
    coupon.cpp \
    drilldownchart.cpp \
    drilldownslice.cpp \
    employe.cpp \
    facture.cpp \
    fournisseur.cpp \
    main.cpp \
    mainwindow.cpp \
    popup.cpp \
    produit.cpp \
    qrcode.cpp \
    smtp.cpp

HEADERS += \
    arduino.h \
    client.h \
    commande.h \
    connection.h \
    coupon.h \
    drilldownchart.h \
    drilldownslice.h \
    employe.h \
    facture.h \
    fournisseur.h \
    mainwindow.h \
    popup.h \
    produit.h \
    qrcode.h \
    smtp.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
    qml.qrc

DISTFILES += \
    sms_notification.py
