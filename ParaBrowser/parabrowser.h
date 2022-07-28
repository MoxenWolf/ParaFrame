#pragma once

#include <source_location>

/*Core*/
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QStringList>

/*Widgets*/
#include <QtWidgets/QWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QFrame>
#include <QtWidgets/qlabel.h>

/*Layouts*/
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGridLayout>

/*Events*/
/*Local*/


class ParaBrowser : public QMainWindow
{
    Q_OBJECT

public:
    ParaBrowser(QWidget *parent = nullptr);
    ~ParaBrowser();

private:
    void uiCreate();
    void conSS();

    QFont fontInfo{ "consolas", 8};
    int topPanelStyle{ QFrame::Panel/* | QFrame::Sunken */};
};

/* Todo: move into common header once shared lib is built */
class ParaCommon : public QObject
{
    Q_OBJECT
public:
    ParaCommon() {}
    virtual ~ParaCommon() {}

    const QStringList INTERFACE_VERSION_SUPPORT{ PARAFRAME_INTERFACE_VERSION, "0.5"  };
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