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
    orderbookdialog.cpp \
    searchrequestwidget.cpp \
    accounthistory.cpp


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
    orderbookdialog.h \
    searchrequestwidget.h \
    accounthistory.h \

FORMS    += \
    addbookdialog.ui \
    library.ui \
    deletebookdialog.ui \
    qsqlconnectiondialog.ui \
    searchaccountwidget.ui \
    editaccountdialog.ui \
    searchbookwidget.ui \
    editbookdialog.ui \
    orderbookdialog.ui \
    searchrequestwidget.ui \
    accounthistory.ui \


RESOURCES += \
    resources.qrc

OTHER_FILES +=
