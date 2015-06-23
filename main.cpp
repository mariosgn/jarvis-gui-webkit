#include "jarvisview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStringList args = a.arguments();
    if (args.contains("--clear"))
    {

    }
    if (args.contains("--imq"))
    {

    }

    JarvisView w;
    w.show();

    return a.exec();
}
