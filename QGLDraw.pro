#-------------------------------------------------
#
# Project created by QtCreator 2014-11-24T17:30:47
#
#-------------------------------------------------

QT       += core gui widgets opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QGLDraw
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    batch.cpp \
    pointtracerender.cpp

HEADERS  += mainwidget.h \
    batch.h \
    batchbase.h \
    pointtracerender.h \
    math3d.h \
