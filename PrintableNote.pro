#-------------------------------------------------
#
# Project created by QtCreator 2015-02-10T14:36:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PrintableNote
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/local/include/opencv\
/usr/local/include/opencv2

LIBS+=/usr/local/lib/libopencv_core.so\
/usr/local/lib/libopencv_imgproc.so\
/usr/local/lib/libopencv_imgcodecs.so\
/usr/local/lib/libopencv_highgui.so
