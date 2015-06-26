QT += core gui webkitwidgets
QT += x11extras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jarvis-gui-webkit
TEMPLATE = app

LIBS += -lX11

SOURCES += main.cpp \
    jarvisview.cpp \
    jarvisviewconfig.cpp

HEADERS  += \
    jarvisview.h \
    jarvisviewconfig.h
