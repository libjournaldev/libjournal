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
    addbookdialog.cpp \
    library.cpp \
    qpsqlconnectiondialog.cpp

HEADERS  += \
    addbookdialog.h \
    library.h \
    qpsqlconnectiondialog.h

FORMS    += \
    addbookdialog.ui \
    library.ui \
    qpsqlconnectiondialog.ui
