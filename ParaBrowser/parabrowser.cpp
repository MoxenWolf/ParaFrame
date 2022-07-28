#include "parabrowser.h"

ParaBrowser::ParaBrowser(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("ParaBrowser for ParaFrame v" + qApp->applicationVersion());

    QFrame* test = new QFrame();

    uiCreate();
}

ParaBrowser::ParaBrowser(ParaBrowserSettings& settings, QWidget* parent) : ParaBrowser(parent)
{
    m_settings = settings;
    if (settings.lastKnownSize.width() > 20 && settings.lastKnownSize.height() > 20)
    {
        this->resize(m_settings.lastKnownSize);
    }
}

ParaBrowser::~ParaBrowser()
{}

void ParaBrowser::closeEvent(QCloseEvent* event)
{
    m_settings.lastKnownSize = this->size();
}

const ParaBrowserSettings ParaBrowser::getSettings()
{
    return m_settings;
}

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
    QFormLayout* layoutMiddleCenter = new QFormLayout();
    frameMiddleCenter->setLayout(layoutMiddleCenter);

    QLabel* lblTestConnection = new QLabel("Event Horizon");
    lblTestConnection->setFont(fontInteract);
    QPushButton* btnTestConnection = new QPushButton("Connect");
    btnTestConnection->setFont(fontInteract);
    connect(btnTestConnection, &QPushButton::clicked, this, &ParaBrowser::slot_connect); //tmp

    layoutMiddleCenter->addRow(lblTestConnection, btnTestConnection);


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
    QHBoxLayout* layoutBottom = new QHBoxLayout();
    frameBottom->setLayout(layoutBottom);

    lblStatusReturn = new QLabel("Return not yet received...");
    lblStatusReturn->setFont(fontInfo);
    layoutBottom->addWidget(lblStatusReturn);
}

void ParaBrowser::conSS()
{

}

/* Slots */
void ParaBrowser::slot_connect(bool checked)
{
    QPalette palette = QGuiApplication::palette();
    // palette.setColor(QPalette::Active, QPalette::ColorRole::Window, QColor(QRandomGenerator::global()->bounded(255), QRandomGenerator::global()->bounded(255), QRandomGenerator::global()->bounded(255)));
    palette.setColor(QPalette::Active, QPalette::ColorRole::Window, PARA_COMMON->getRandColor());
    this->setPalette(palette);

    ParaLib x;
    int y = x.returnInt();

    lblStatusReturn->setText("Return is: " + QString::number(y));
}
