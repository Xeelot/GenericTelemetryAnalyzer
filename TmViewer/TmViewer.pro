#-------------------------------------------------
#
# Project created by QtCreator 2015-11-23T17:24:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = TmViewer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dictionary.cpp \
    datamanager.cpp \
    telemetry.cpp \
    fileserializer.cpp \
    dictmodel.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    constants.h \
    dictionary.h \
    datamanager.h \
    telemetry.h \
    fileserializer.h \
    ifileobject.h \
    dictmodel.h \
    qcustomplot.h

FORMS    += mainwindow.ui
