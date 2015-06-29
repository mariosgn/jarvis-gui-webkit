#include "jarvisview.h"
#include <QWebFrame>
#include <QWebElement>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QX11Info>


bool JarvisView::eventFilter(QObject *, QEvent *event)
{
    if (  event->type() == QEvent::KeyPress )
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if ( keyEvent->key() == Qt::Key_Escape)
        {
            hide();
        }
    }
    return false;
}

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xmd.h>
#include <X11/Xutil.h>

JarvisView::JarvisView( const JarvisConfig& config ) :
    QWebView( QApplication::desktop()->screen() ),
    m_sConfig(config)
{
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

    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_X11NetWmWindowTypeDesktop, true);
    setAttribute(Qt::WA_X11NetWmWindowTypeUtility, true);
    //    setAttribute(Qt::WA_X11DoNotAcceptFocus, true);

//    installEventFilter(this);

    setWindowFlags(Qt::FramelessWindowHint|Qt::NoDropShadowWindowHint|Qt::WindowStaysOnBottomHint|Qt::X11BypassWindowManagerHint);
    setWindowTitle("jarvis-view-webkit");

    load(QUrl::fromLocalFile( config.confProp(JarvisConfig::PropThemeFile).toString() ));
    m_bForceX11Desktop = config.confProp(JarvisConfig::PropForceDesktop).toBool();

    m_pX11Events = new X11EventPoller();
    connect(m_pX11Events, SIGNAL(activated()), this, SLOT(toggleVisibility()));
//    m_pX11Events->start();

    setGeometry( m_sConfig.confProp(JarvisConfig::PropX).toInt(),
                 m_sConfig.confProp(JarvisConfig::PropY).toInt(),
                 m_sConfig.confProp(JarvisConfig::PropWidth).toInt(),
                 m_sConfig.confProp(JarvisConfig::PropHeight).toInt()
                 );

    if ( m_bForceX11Desktop )
    {
        XLowerWindow(QX11Info::display(),  winId());
//        XReparentWindow(QX11Info::display(), winId(), QX11Info::appRootWindow(), 0, 0);
    }
}

void JarvisView::showEvent(QShowEvent *)
{
//    setGeometry( m_sConfig.confProp(JarvisConfig::PropX).toInt(),
//              m_sConfig.confProp(JarvisConfig::PropY).toInt(),
//              m_sConfig.confProp(JarvisConfig::PropWidth).toInt(),
//              m_sConfig.confProp(JarvisConfig::PropHeight).toInt()
//              );


}



void JarvisView::toggleVisibility()
{
    setVisible(!isVisible());
}

void X11EventPoller::run()
{

    QByteArray displayName = qgetenv("DISPLAY");
    Display *display = XOpenDisplay(displayName.constData());
    Window root = QX11Info::appRootWindow();

    XEvent xev;
    int keycode =  XKeysymToKeycode(display,XK_F12);
    unsigned int modifiers = ControlMask;

    for( uint irrelevantBitsMask = 0; irrelevantBitsMask <= 0xff; irrelevantBitsMask++ ) {
        XGrabKey( display, keycode, modifiers | irrelevantBitsMask, root, False, GrabModeAsync, GrabModeAsync);
    }


    while (666) {
        XNextEvent(display, &xev);
        switch(xev.type)
        {
        case KeyPress:
            emit activated();

        default:
            break;
        }
    }

    XFlush(display);
    XCloseDisplay(display);
}
