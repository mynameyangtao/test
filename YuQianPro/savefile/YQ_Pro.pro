#-------------------------------------------------
#
# Project created by QtCreator 2022-05-05T13:32:27
#
#-------------------------------------------------

QT       += core gui network axcontainer
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = YQ_Pro
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        contents.cpp \
        historycharts.cpp \
        historyinfo.cpp \
        homepage.cpp \
        main.cpp \
        qcustomplot.cpp \
        testpoint_info.cpp \
        widget.cpp

HEADERS += \
        contents.h \
        historycharts.h \
        historyinfo.h \
        homepage.h \
        qcustomplot.h \
        testpoint_info.h \
        widget.h

FORMS += \
        contents.ui \
        historycharts.ui \
        historyinfo.ui \
        homepage.ui \
        testpoint_info.ui \
        widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
