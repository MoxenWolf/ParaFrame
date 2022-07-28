#include "parabrowser.h"

/*Core*/
#include <QtWidgets/QApplication>
#include <QtGui/QIcon>
/*Widgets*/
/*Layouts*/
/*Events*/
/*Local*/


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/Images/logo_ico"));
    ParaBrowser w;
    w.show();
    return a.exec();
}
