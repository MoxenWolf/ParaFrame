#pragma once

//#include <QtCore/qglobal.h>

#include <source_location>

/*Core*/
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVector>
#include <QtCore/QStringList>
#include <QtCore/QSize>
#include <QtGui/QPalette>
#include <QtGui/QColor>
#include <QtCore/QRandomGenerator>

/*Widgets*/
#include <QtWidgets/QWidget>

/*Layouts*/
/*Events*/
/*Local*/

namespace ParaLib
{
    class ParaCommon : public QObject
    {
        Q_OBJECT

    public:
        ParaCommon(QWidget* parent = Q_NULLPTR);
        virtual ~ParaCommon() {}

        int returnInt();

        const QStringList INTERFACE_VERSION_SUPPORT{ PARAFRAME_INTERFACE_VERSION, "0.5" };

        const QColor getRandColor()
        {
            return QColor(QRandomGenerator::global()->bounded(255), QRandomGenerator::global()->bounded(255), QRandomGenerator::global()->bounded(255));
        }
    };

    Q_GLOBAL_STATIC(ParaCommon, PARA_COMMON)

    enum class PARAFRAME_ERROR {
        PLUGIN_LOAD_FAILED_MODULE_NOT_FOUND,
        PLUGIN_LOAD_FAILED_BAD_DEFINITION_FILE
    };
    Q_DECLARE_METATYPE(PARAFRAME_ERROR)
}

#ifdef _DEBUG
#include <QtCore/qdebug.h>
#include <source_location>

#define PF_DEBUG(message) {\
		    qDebug() << "[[PARAFRAME-DEBUG]]" << std::source_location::current().function_name() << ":" << std::source_location::current().line() << "-" << message;\
		    }
#else
#define PF_DEBUG(message)
#endif
