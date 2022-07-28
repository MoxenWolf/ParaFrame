#pragma once

#include <source_location>

/*Core*/
#include <QtCore/QObject>
#include <QtWidgets/QApplication>
#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QStringList>
#include <QtCore/QSize>
#include <QCloseEvent>
#include <QtGui/QPalette>
#include <QtGui/QColor>
#include <QtCore/QRandomGenerator>

/*Widgets*/
#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

/*Layouts*/
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QFormLayout>

/*Events*/
/*Local*/
#include "paralib.h"

struct ParaBrowserSettings
{
    QSize lastKnownSize{-1, -1};
};

class ParaBrowser : public QMainWindow
{
    Q_OBJECT

public:
    ParaBrowser(QWidget *parent = Q_NULLPTR);
    ParaBrowser(ParaBrowserSettings& settings, QWidget* parent = Q_NULLPTR);
    ~ParaBrowser();

    const ParaBrowserSettings getSettings();
protected:
    void closeEvent(QCloseEvent*) override;
private:
    void uiCreate();
    void conSS();

    QLabel* lblStatusReturn;

    ParaBrowserSettings m_settings;
    QFont fontInfo{ "consolas", 8};
    QFont fontInteract{ "consolas", 10 };
    int topPanelStyle{ QFrame::Panel/* | QFrame::Sunken */};
private slots:
    void slot_connect(bool);
};

/* Todo: move into common header once shared lib is built */
class ParaCommon : public QObject
{
    Q_OBJECT
public:
    ParaCommon() {}
    virtual ~ParaCommon() {}

    const QStringList INTERFACE_VERSION_SUPPORT{ PARAFRAME_INTERFACE_VERSION, "0.5"  };

    const QColor getRandColor()
    {
        return QColor(QRandomGenerator::global()->bounded(255), QRandomGenerator::global()->bounded(255), QRandomGenerator::global()->bounded(255));
    }
};
Q_GLOBAL_STATIC(ParaCommon, PARA_COMMON)

#ifdef _DEBUG
    #include <QtCore/qdebug.h>
    #include <source_location>

    #define PF_DEBUG(message) {\
		    qDebug() << "[[PARAFRAME-DEBUG]]" << std::source_location::current().function_name() << ":" << std::source_location::current().line() << "-" << message;\
		    }
#else
    #define PF_DEBUG(message)
#endif