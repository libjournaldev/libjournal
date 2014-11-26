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
    deletebookdialog.cpp \
    searchbookdialog.cpp \
    qsqlconnectiondialog.cpp \
    infobuttondelegate.cpp \
    libjsqlmodel.cpp \
    searchaccountwidget.cpp \
    editaccountdialog.cpp

HEADERS  += \
    addbookdialog.h \
    library.h \
    spinbox.h \
    deletebookdialog.h \
    searchbookdialog.h \
    qsqlconnectiondialog.h \
    infobuttondelegate.h \
    libjsqlmodel.h \
    searchaccountwidget.h \
    editaccountdialog.h

FORMS    += \
    addbookdialog.ui \
    library.ui \
    deletebookdialog.ui \
    searchbookdialog.ui \
    qsqlconnectiondialog.ui \
    searchaccountwidget.ui \
    editaccountdialog.ui

RESOURCES += \
    resources.qrc
