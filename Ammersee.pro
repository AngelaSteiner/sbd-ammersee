#-------------------------------------------------
#
# Project created by QtCreator 2016-04-26T11:45:46
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ammersee
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        dbank.cpp \
        event_add.cpp \
    teilnehmer.cpp \
    teilnehmer_add.cpp \
    duringevent.cpp

HEADERS  += mainwindow.h \
        dbank.h \
        event_add.h \
    teilnehmer.h \
    teilnehmer_add.h \
    duringevent.h

FORMS    += mainwindow.ui \
        event_add.ui \
    teilnehmer.ui \
    teilnehmer_add.ui \
    duringevent.ui
