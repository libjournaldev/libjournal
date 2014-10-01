#-------------------------------------------------
#
# Project created by QtCreator 2014-09-29T13:24:00
#
#-------------------------------------------------

QT       += sql core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LibJournal
TEMPLATE = app


SOURCES += main.cpp\
        libcontroller.cpp \
    qpsqlconnectionwidget.cpp \
    addbookdialog.cpp

HEADERS  += libcontroller.h \
    qpsqlconnectionwidget.h \
    addbookdialog.h

FORMS    += libcontroller.ui \
    qpsqlconnectionwidget.ui \
    addbookdialog.ui
