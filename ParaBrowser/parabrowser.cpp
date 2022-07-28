#include "parabrowser.h"

ParaBrowser::ParaBrowser(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("ParaBrowser for ParaFrame v" + QString(PARAFRAME_VERSION));
}

ParaBrowser::~ParaBrowser()
{}
