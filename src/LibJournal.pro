#-------------------------------------------------
#
# Project created by QtCreator 2014-09-29T13:24:00
#
#-------------------------------------------------

QT       += sql core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LibJournal
TEMPLATE = app


SOURCES += main.cpp\
    addbookdialog.cpp \
    library.cpp \
    deletebookdialog.cpp \
    qsqlconnectiondialog.cpp \
    searchaccountwidget.cpp \
    editaccountdialog.cpp \
    searchbookwidget.cpp \
    editbookdialog.cpp \
<<<<<<< HEAD
    orderbookdialog.cpp \
    searchrequestwidget.cpp
=======
    accounthistory.cpp \
    orderbookdialog.cpp
>>>>>>> origin/master

HEADERS  += \
    addbookdialog.h \
    library.h \
    spinbox.h \
    deletebookdialog.h \
    qsqlconnectiondialog.h \
    searchaccountwidget.h \
    editaccountdialog.h \
    searchbookwidget.h \
    editbookdialog.h \
<<<<<<< HEAD
    orderbookdialog.h \
    searchrequestwidget.h
=======
    accounthistory.h \
    orderbookdialog.h
>>>>>>> origin/master

FORMS    += \
    addbookdialog.ui \
    library.ui \
    deletebookdialog.ui \
    qsqlconnectiondialog.ui \
    searchaccountwidget.ui \
    editaccountdialog.ui \
    searchbookwidget.ui \
    editbookdialog.ui \
<<<<<<< HEAD
    orderbookdialog.ui \
    searchrequestwidget.ui
=======
    accounthistory.ui \
    orderbookdialog.ui
>>>>>>> origin/master

RESOURCES += \
    resources.qrc
