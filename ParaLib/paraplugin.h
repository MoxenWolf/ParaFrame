#pragma once

/*Core*/
#include <QObject>
#include <QtCore/QString>
#include <QtCore/QSet>
#include <QtCore/QList>
#include <QtCore/QVector>
#include <QtCore/QQueue>
#include <QtCore/QStringList>
#include <QtCore/QByteArray>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtCore/QIODevice>
#include <QtCore/QLibrary>
#include <QtCore/QJsonObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonValue>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonValueRef>

/*Local*/
#include "paralib.h"

namespace ParaLib {

	class ParaPlugin  : public QObject
	{
		Q_OBJECT

	public:
		ParaPlugin(QObject *parent);
		~ParaPlugin();

		ParaCommon::PARAFRAME_ERROR lastError();

		bool loadPlugin(const QString&);

		union u_pcast
		{
			void (ParaPlugin::*pluginEnabled_bound)();
			void (*test)();
		}fnptr;

	private:
		QQueue<ParaCommon::PARAFRAME_ERROR> errors;

		QString paraInterfaceVersionUsed;
		QString paraPluginUsed;
		QFileInfo paraPluginLocation;
		QString paraName;
		QString paraDescription;
		//TODO QPixmap for png

		QLibrary* pluginLib = Q_NULLPTR;

		/* interfaces into plugin */
		ParaLib::IgetSupportedFunctions getSupportedFunctions;
		ParaLib::IpluginEnable pluginEnable;
		ParaLib::IsetPluginEnabled setPluginEnabledCb;

		ParaLib::IParaBase iParaBase; // all f() pointers for IParaBase

		void pluginEnabled_bound();
	};
}


