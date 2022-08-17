#include "paraplugin.h"

using namespace ParaLib;

ParaPlugin::ParaPlugin(QObject *parent)
	: QObject(parent)
{}

ParaPlugin::~ParaPlugin()
{}

ParaCommon::PARAFRAME_ERROR ParaPlugin::lastError()
{
	return errors.length() > 0 ? errors.dequeue() : ParaCommon::PARAFRAME_ERROR::NO_ERROR;
}

bool ParaPlugin::loadPlugin(const QString& path)
{
	bool success = false;

	QFileInfo paraFileInfo{ path };
	QFile paraFile{ path };

	if (paraFileInfo.exists() && paraFileInfo.isReadable() && paraFile.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QByteArray fileData = paraFile.readAll();
		paraFile.close();

		fileData.replace(QByteArray("\\"), QByteArray("\\\\"));

		QJsonDocument jsonDoc = QJsonDocument::fromJson(fileData);

		if (jsonDoc.object().contains("plugin") && jsonDoc.object().contains("interface_version")) //both keys are required
		{
			paraInterfaceVersionUsed = jsonDoc["interface_version"].toString();
			QStringList x = PARA_COMMON->INTERFACE_VERSION_SUPPORT;
			
			if (PARA_COMMON->INTERFACE_VERSION_SUPPORT.contains(paraInterfaceVersionUsed))
			{
				paraPluginUsed = jsonDoc["plugin"].toString();

				//TODO: Change to be os-independent
				//TODO: Change to search through known plugin directories
				paraPluginLocation = QFileInfo{ paraFileInfo.dir().canonicalPath() + "/" + paraPluginUsed + ".dll" };
				paraName = jsonDoc.object().contains("name") ? jsonDoc["name"].toString() : paraFileInfo.baseName();
				paraDescription = jsonDoc.object().contains("description") ? jsonDoc["description"].toString() : "";

				success = true;
			}
			else
			{
				errors.enqueue(ParaCommon::PARAFRAME_ERROR::PLUGIN_PARA_MALFORMED);
			}
		}
		else
		{
			errors.enqueue(ParaCommon::PARAFRAME_ERROR::PLUGIN_PARA_MALFORMED);
		}
	}
	else
	{
		errors.enqueue(ParaCommon::PARAFRAME_ERROR::PLUGIN_READ_ERROR);
	}

	return success;
}


