#include "parabrowser.h"

ParaBrowser::ParaBrowser(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("ParaBrowser for ParaFrame v" + QString(PARAFRAME_VERSION));

    QFrame* test = new QFrame();

    uiCreate();

    //this->adjustSize();
}

ParaBrowser::~ParaBrowser()
{}

void ParaBrowser::uiCreate()
{
    QVBoxLayout* layoutCentral = new QVBoxLayout();
    QFrame* frameCentral = new QFrame();
    this->setCentralWidget(frameCentral);
    this->centralWidget()->setLayout(layoutCentral);

    /* Top Frame */
    QFrame* frameTopInfo = new QFrame();
    frameTopInfo->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
    frameTopInfo->setFrameStyle(topPanelStyle);
    layoutCentral->addWidget(frameTopInfo);
    QHBoxLayout* layoutTopInfo = new QHBoxLayout();
    frameTopInfo->setLayout(layoutTopInfo);
    QLabel* lblInterfaceVersionOutput = new QLabel();
    lblInterfaceVersionOutput->setFont(fontInfo);
    lblInterfaceVersionOutput->setText("Supporting ParaFrame Interfacing Versions: <b>[" + PARA_COMMON->INTERFACE_VERSION_SUPPORT.join("] [") + QString("]</b>"));
    layoutTopInfo->addWidget(lblInterfaceVersionOutput);
    

    /* Middle Frame Wrap */
    QFrame* frameMiddleContentWrap = new QFrame();
    layoutCentral->addWidget(frameMiddleContentWrap);
    QHBoxLayout* layoutMiddleContentWrap = new QHBoxLayout();
    layoutMiddleContentWrap->setContentsMargins(0, 0, 0, 0);
    frameMiddleContentWrap->setLayout(layoutMiddleContentWrap);
    frameMiddleContentWrap->setMinimumHeight(100);
    

    /* Middle Left */
    QFrame* frameMiddleLeft = new QFrame();
    layoutMiddleContentWrap->addWidget(frameMiddleLeft);
    frameMiddleLeft->setFrameStyle(topPanelStyle);
    frameMiddleLeft->setFixedWidth(50);

    /* Middle Center */
    QFrame* frameMiddleCenter = new QFrame();
    layoutMiddleContentWrap->addWidget(frameMiddleCenter);
    frameMiddleCenter->setFrameStyle(topPanelStyle);
    frameMiddleCenter->setMinimumWidth(200);

    /* Middle Right */
    QFrame* frameMiddleRight = new QFrame();
    layoutMiddleContentWrap->addWidget(frameMiddleRight);
    frameMiddleRight->setFrameStyle(topPanelStyle);
    frameMiddleRight->setFixedWidth(50);

    /* Bottom Frame */
    QFrame* frameBottom = new QFrame();
    layoutCentral->addWidget(frameBottom);
    frameBottom->setFrameStyle(topPanelStyle);
    frameBottom->setFixedHeight(50);

    


}

void ParaBrowser::conSS()
{

}
