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
    lblInterfaceVersionOutput->setText("Supporting ParaFrame Interfacing Versions: <b>[" + ParaLib::PARA_COMMON->INTERFACE_VERSION_SUPPORT.join("] [") + QString("]</b>"));
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
{}

/* Slots */
void ParaBrowser::slot_connect(bool checked)
{
    QPalette palette = QGuiApplication::palette();
    // palette.setColor(QPalette::Active, QPalette::ColorRole::Window, QColor(QRandomGenerator::global()->bounded(255), QRandomGenerator::global()->bounded(255), QRandomGenerator::global()->bounded(255)));
    palette.setColor(QPalette::Active, QPalette::ColorRole::Window, ParaLib::PARA_COMMON->getRandColor());
    this->setPalette(palette);

    libEventHorizon = new QLibrary("C:/d21/ParaFrame/x64/Debug/DllEventHorizon.dll");
    libEventHorizon->load();

    if (libEventHorizon->isLoaded())
    {
        PF_DEBUG("loaded...");

        try
        {
            /*this->pluginEnable = (protoPluginEnable)libEventHorizon->resolve("pluginEnableExport");
            this->pluginDisable = (protoPluginDisable)libEventHorizon->resolve("pluginDisableExport");*/

            this->pluginEnable = (protoPluginEnable)libEventHorizon->resolve("pluginEnableExport");
            this->pluginDisable = (protoPluginDisable)libEventHorizon->resolve("pluginDisable");
            this->getInterfaceVersion = (protoPluginGetInterfaceVersion)libEventHorizon->resolve("getInterfaceVersion");

            PF_DEBUG("resolve success...");
        }
        catch (...)
        {
            PF_DEBUG("resolve failed...");
        }

        if (this->pluginEnable)
        {
            PF_DEBUG("calling pluginEnable...");
            int value = this->pluginEnable();
            lblStatusReturn->setText("Value: " + QString::number(value));
        }

        if (this->getInterfaceVersion)
        {
            std::list<std::string> value = this->getInterfaceVersion();
            if (value.size() > 0)
            {
                PF_DEBUG(QString::fromStdString(value.front()));
            }
        }
    }

    /*if (libEventHorizon->isLoaded())
    {
        PF_DEBUG("loaded");
        try
        {
            ehDoEmpty = (protoDoEmpty)libEventHorizon->resolve("doEmpty");
            ehIncInt = (protoIncInt)libEventHorizon->resolve("incInt");
        }
        catch (...)
        {
            PF_DEBUG("resolve failed");
        }

        if (ehDoEmpty)
        {
            PF_DEBUG("...calling doEmpty...");
            ehDoEmpty();

            
        }

        if (ehIncInt)
        {
            PF_DEBUG("...calling incInt...");
            int value = ehIncInt(10);
            lblStatusReturn->setText("Post incInt(10): " + QString::number(value));
        }
        
        
    }*/
    


    /*ParaLib::ParaCommon x;
    lblStatusReturn->setText("Return is: " + QString::number(x.returnInt()));

    PF_DEBUG("testing debug output")*/
}
