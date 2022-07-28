#include "parabrowser.h"

ParaBrowser::ParaBrowser(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("ParaBrowser for ParaFrame v" + QString(PARAFRAME_VERSION));

    QFrame* test = new QFrame();

    uiCreate();

    this->adjustSize();
}

ParaBrowser::~ParaBrowser()
{}

void ParaBrowser::uiCreate()
{
    QVBoxLayout* layoutCentral = new QVBoxLayout();
    QFrame* frameCentral = new QFrame();
    this->setCentralWidget(frameCentral);
    this->centralWidget()->setLayout(layoutCentral);

    /*QLabel* x = new QLabel("testing");
    layoutCentral->addWidget(x);*/

    frameTopInfo = new QFrame(this);
    frameTopInfo->setFrameStyle(topPanelStyle);
    layoutCentral->addWidget(frameTopInfo);
    QHBoxLayout* layoutTopInfo = new QHBoxLayout();
    frameTopInfo->setLayout(layoutTopInfo);
    QLabel* lblInterfaceVersionOutput = new QLabel();
    lblInterfaceVersionOutput->setFont(fontInfo);
    lblInterfaceVersionOutput->setText("Supporting ParaFrame Interfacing Versions: <b>[" + PARA_COMMON->INTERFACE_VERSION_SUPPORT.join("] [") + QString("]</b>"));
    layoutTopInfo->addWidget(lblInterfaceVersionOutput);
}

void ParaBrowser::conSS()
{

}
