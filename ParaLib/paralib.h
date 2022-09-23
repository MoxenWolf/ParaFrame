#pragma once

//#include <QtCore/qglobal.h>

//#include "paraplugin.h"

/*stdlib*/
#include <string>
#include <list>
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

#define PARAFRAME_VERSION "0.0.1"
#define CURRENT_PARAFRAME_INTERFACE_VERSION "0.1b"

namespace ParaLib {

    /* *** Interface Defs *** */

    //TODO make into singal template for protosignals and singal template for protoslots
    template<typename R>
    using FT_SIG = void(*)(R);

    FT_SIG<int> xt;

    void testing(int v)
    {
        return v;
    }

    //directs
    typedef void (*ft_void_)();
    typedef void (*ft_void_charstar_out)(char**);
    typedef void (*ft_void_int)(int);
    typedef void (*ft_void_float)(float);
    typedef int (*ft_int_)();
    
    //callback sets (set callback to pointer to function with signature...)
    typedef void (*ft_cb_void_)(void(*)());
    typedef void (*ft_cb_int_)(int(*)());
    typedef void (*ft_cb_void_bool)(void(*)(bool, int));
    

    struct IParaBase
    {
        struct ProtoSignals
        {

        };
        
        struct ProtoSlots
        {

        };

        ft_void_charstar_out getSupportedInterfaceVersions;
        ft_void_charstar_out getPluginInterfaces;
        ft_int_ pluginEnable;
        ft_cb_void_bool setPluginEnabled_cb;
    };

    /* *** Utility *** */
    class ParaCommon : public QObject
    {
        Q_OBJECT

    public:
        ParaCommon(QWidget* parent = Q_NULLPTR) : QObject{ parent } {};
        virtual ~ParaCommon() {}

        const QStringList INTERFACE_VERSION_SUPPORT{ "0.1a", CURRENT_PARAFRAME_INTERFACE_VERSION};

        const QColor getRandColor()
        {
            return QColor(QRandomGenerator::global()->bounded(255), 
                QRandomGenerator::global()->bounded(255), 
                QRandomGenerator::global()->bounded(255));
        }

        enum class PARAFRAME_ERROR {
            NO_ERROR = 0,
            INDETERMINATE = 1,
            PLUGIN_READ_ERROR,
            PLUGIN_PARA_MALFORMED,
            PLUGIN_LIB_CANNOT_LOAD,
            PLUGIN_LIB_CRITICAL_FUNCTION_NOT_RESOLVED
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

#if __cplusplus >= 202002L

    // C++20 (and later) code
#endif
