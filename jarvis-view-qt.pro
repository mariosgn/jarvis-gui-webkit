QT       += core gui webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jarvis-gui-webkit
TEMPLATE = app


SOURCES += main.cpp \
    jarvisview.cpp \
    jarvisviewconfig.cpp

HEADERS  += \
    jarvisview.h \
    jarvisviewconfig.h

FORMS    +=
