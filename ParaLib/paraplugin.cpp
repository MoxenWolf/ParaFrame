#include "paraplugin.h"

using namespace ParaLib;

ParaPlugin::ParaPlugin(QObject *parent)
	: QObject(parent)
{
	fnptr.pluginEnabled_bound = &ParaPlugin::pluginEnabled_bound;

}

ParaPlugin::~ParaPlugin()
{
	if (pluginLib)
	{
		PF_DEBUG("unloading pre");
		pluginLib->unload();
		PF_DEBUG("unloading post");
	}
	
}

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

				/* *** load plugin library *** */
				pluginLib = new QLibrary(paraPluginLocation.canonicalFilePath());
				pluginLib->load();

				if (pluginLib->isLoaded())
				{
					try
					{
						getSupportedFunctions = (ParaLib::IgetSupportedFunctions)pluginLib->resolve("getSupportedFunctions_translator");
						pluginEnable = (ParaLib::IpluginEnable)pluginLib->resolve("pluginEnable_translator");
						setPluginEnabledCb = (ParaLib::IsetPluginEnabled)pluginLib->resolve("setCbPluginEnabled_translator");
					}
					catch (...)
					{
						errors.enqueue(ParaCommon::PARAFRAME_ERROR::PLUGIN_LIB_CRITICAL_FUNCTION_NOT_RESOLVED);
					}
					
					if (getSupportedFunctions)
					{
						//QList<QString> value((std::list<std::string>)getSupportedFunctions());
						//std::vector<std::string> value = getSupportedFunctions();
						char* supportedFunctions;
						getSupportedFunctions(&supportedFunctions);
						std::string value{ supportedFunctions };
						delete supportedFunctions;
						
						//PF_DEBUG(QString::fromStdString(value.front()));
						PF_DEBUG(QString::fromStdString(value));
						success = true;
					}

					if (setPluginEnabledCb)
					{
						//setPluginEnabledCb(&ParaLib::pluginEnabled_test);
						//setPluginEnabledCb(&ParaLib::ParaPlugin::pluginEnabled_static);
						//setPluginEnabledCb(&ParaPlugin::pluginEnabled_bound);
						//void* (*object_ptr)() = &pluginEnabled_bound;

						setPluginEnabledCb(fnptr.test);

						PF_DEBUG("setPluginEnabledCb resolved...");
						success = true;
					}

					if (pluginEnable)
					{
						int value = pluginEnable();
						PF_DEBUG(QString::number(value));
						success = true;
					}
				}
				else
				{
					errors.enqueue(ParaCommon::PARAFRAME_ERROR::PLUGIN_LIB_CANNOT_LOAD);
				}
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

void ParaLib::ParaPlugin::pluginEnabled_static()
{
	PF_DEBUG("inside pluginEnabled (static)");
}

void ParaLib::ParaPlugin::pluginEnabled_bound()
{
	PF_DEBUG("inside pluginEnabled (bound)");
}

void ParaLib::pluginEnabled_test()
{
	PF_DEBUG("inside pluginEnabled (solo)...");
}
