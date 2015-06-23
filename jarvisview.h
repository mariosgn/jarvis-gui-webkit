#ifndef JARVISWIDGET_H
#define JARVISWIDGET_H

#include <QObject>
#include <QWebView>
#include <QWidget>

class JarvisView : public QWebView
{
    Q_OBJECT

public:
    JarvisView();

};

#endif // JARVISWIDGET_H
