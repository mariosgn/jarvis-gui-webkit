#include "jarvisview.h"
#include <QWebFrame>
#include <QWebElement>
#include <QDebug>

JarvisView::JarvisView()
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::FramelessWindowHint|Qt::NoDropShadowWindowHint|Qt::BypassWindowManagerHint|Qt::X11BypassWindowManagerHint);
    setWindowTitle("jarvis-view-webkit");
    QPalette p = palette();
    p.setBrush(QPalette::Base, Qt::transparent);
    page()->setPalette(p);
    setAttribute(Qt::WA_OpaquePaintEvent, false);
    QLinearGradient gradient;
    gradient.setColorAt(0.0, QColor(249, 247, 96));
    gradient.setColorAt(1.0, QColor(235, 203, 32));
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    page()->mainFrame()->setScrollBarPolicy( Qt::Vertical, Qt::ScrollBarAlwaysOff );
    page()->mainFrame()->setScrollBarPolicy( Qt::Horizontal, Qt::ScrollBarAlwaysOff );


    load(QUrl::fromLocalFile("/home/mario/Dropbox/Dev/Jarvis/nodejs-test/harmattan-like-demo/index.html"));
}

