#include "jarvisview.h"
#include "jarvisviewconfig.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStringList args = a.arguments();
    if (!args.contains("--view"))
    {
        qDebug() << "Error: a view name required.";
        qDebug() << "--view viewname";
        return 0;
    }

    int viewIdx = args.indexOf("--view");
    if (args.size()<viewIdx+2)
    {
        qDebug() << "Error: a view name required.";
        qDebug() << "--view viewname";
        return 0;
    }
    QString view = args[++viewIdx];

    JarvisConfig conf( view );

    if ( !conf.isValid() )
    {
        return 0;
    }

    JarvisView w(conf);
    w.show();

    return a.exec();
}
