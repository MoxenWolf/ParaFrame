#pragma once

//#include <QtCore/qglobal.h>

//#include "paraplugin.h"

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
    /* *** Utility *** */
    class ParaCommon : public QObject
    {
        Q_OBJECT

    public:
        ParaCommon(QWidget* parent = Q_NULLPTR) : QObject{ parent } {};
        virtual ~ParaCommon() {}

        const QStringList INTERFACE_VERSION_SUPPORT{ PARAFRAME_INTERFACE_VERSION};

        const QColor getRandColor()
        {
            return QColor(QRandomGenerator::global()->bounded(255), 
                QRandomGenerator::global()->bounded(255), 
                QRandomGenerator::global()->bounded(255));
        }

        enum class PARAFRAME_ERROR {
            PLUGIN_LOAD_FAILED_MODULE_NOT_FOUND,
            PLUGIN_LOAD_FAILED_BAD_DEFINITION_FILE
        };
    };

    Q_GLOBAL_STATIC(ParaCommon, PARA_COMMON);
    Q_DECLARE_METATYPE(ParaCommon::PARAFRAME_ERROR);
}

/* *** Macros and Defines*** */
#ifdef _DEBUG
#include <QtCore/QDebug>
#include <source_location>

#define PF_DEBUG(message) {\
		    qDebug() << "[[PARAFRAME-DEBUG]]" << std::source_location::current().function_name() << ":" << std::source_location::current().line() << "-" << message;\
		    }
#else
#define PF_DEBUG(message)
#endif
