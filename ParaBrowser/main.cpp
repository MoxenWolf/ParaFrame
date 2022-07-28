#include "parabrowser.h"

/*Core*/
#include <QtWidgets/QApplication>
#include <QtGui/QIcon>
#include <QtGui/QFont>

/*Widgets*/
/*Layouts*/
/*Events*/
/*Local*/


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/Images/logo_ico"));
    a.setFont(QFont("Consolas"));
    ParaBrowser w;
    w.show();
    return a.exec();
}
