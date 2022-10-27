#include "temptestapp.h"
#include "dan_tmp.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    XBoxController x;
    x.pluginSetup();




    QApplication a(argc, argv);
    TempTestApp w;
    w.show();
    return a.exec();
}
