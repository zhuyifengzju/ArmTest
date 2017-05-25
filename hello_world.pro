#-------------------------------------------------
#
# Project created by QtCreator 2017-05-03T20:47:17
#
#-------------------------------------------------

QT       += core gui printsupport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hello_world
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    window.cpp \
    glwidget.cpp \
    logo.cpp \
    dataflow.cpp \
    qcustomplot.cpp \
    plotwidget.cpp \
    leg.cpp \
    udp.cpp \
    lowerarm1.cpp \
    lowerarm2.cpp \
    lowerarm3.cpp \
    shoulder.cpp \
    bat.cpp \
    upperarm2.cpp \
    upperarm1.cpp

HEADERS  += mainwindow.h \
    window.h \
    glwidget.h \
    logo.h \
    dataflow.h \
    qcustomplot.h \
    plotwidget.h \
    leg.h \
    udp.h \
    lowerarm1.h \
    lowerarm2.h \
    bat.h \
    lowerarm3.h \
    upperarm1.h \
    upperarm2.h \
    shoulder.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    shaders/shad.frag \
    shaders/shad.vert \
    shaders/shad1.frag \
    shaders/shad1.vert

RESOURCES += \
    resources.qrc

DISTFILES += \
    ../Documents/graph/lighting/hello_world/shaders/shad2.frag \
    ../Documents/graph/lighting/hello_world/shaders/shad2.vert \
    x_r.txt \
    y_r.txt
