#ifndef JARVISWIDGET_H
#define JARVISWIDGET_H

#include "jarvisviewconfig.h"

#include <QObject>
#include <QWebView>
#include <QWidget>
#include <QThread>

class X11EventPoller : public QThread
{
    Q_OBJECT
    void run() Q_DECL_OVERRIDE ;
signals:
    void activated();
};

class JarvisView : public QWebView
{
    Q_OBJECT

public:
    JarvisView( const JarvisConfig& config );
    bool eventFilter(QObject *o, QEvent *e);

public slots:
    void toggleVisibility();

protected:
    virtual void showEvent(QShowEvent * event);

private:
    bool m_bForceX11Desktop;
    X11EventPoller* m_pX11Events;
    const JarvisConfig& m_sConfig;
};

#endif // JARVISWIDGET_H
