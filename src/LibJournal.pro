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
    qpsqlconnectionwidget.cpp \
    addbookdialog.cpp \
    library.cpp

HEADERS  += \
    qpsqlconnectionwidget.h \
    addbookdialog.h \
    library.h

FORMS    += \
    qpsqlconnectionwidget.ui \
    addbookdialog.ui \
    library.ui
