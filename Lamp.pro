#-------------------------------------------------
#
# Project created by QtCreator 2013-08-20T13:49:59
#
#-------------------------------------------------

QMAKE_CXX       =  g++-4.8
QMAKE_CXXFLAGS  = -std=c++11
INCLUDEPATH    += /usr/local/include
INCLUDEPATH    += /usr/local/opt/qt5/include
LIBS           += -L/usr/local/lib
LIBS           += -L/usr/local/opt/qt5/lib
LIBS           += -lm -larmadillo

QT += core
QT -= gui

TARGET  = Lamp
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    Lamp.cpp

HEADERS += \
    Lamp.h
