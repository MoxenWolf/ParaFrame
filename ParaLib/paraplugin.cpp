#include "paraplugin.h"

using namespace ParaLib;

ParaPlugin::ParaPlugin(QObject *parent)
	: QObject(parent)
{
	fnptr.pluginEnabled_bound_tmp = &ParaPlugin::pluginEnabled_bound;
	

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
	//fnptr.pluginEnabled_bound_tmp = &this->pluginEnabled_bound;
	fnptr.pluginEnabled_bound_tmp = &ParaPlugin::pluginEnabled_bound;

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
						iParaBase.getSupportedInterfaceVersions = (ParaLib::ft_void_charstar_out)pluginLib->resolve("getSupportedInterfaceVersions_ex");
						iParaBase.getPluginInterfaces = (ParaLib::ft_void_charstar_out)pluginLib->resolve("getPluginInterfaces_ex");

						iParaBase.pluginEnable = (ParaLib::ft_int_)pluginLib->resolve("pluginEnable_ex");
						iParaBase.setPluginEnabled_cb = (ParaLib::ft_cb_void_bool)pluginLib->resolve("setCbPluginEnabled_ex");
						
					}
					catch (...)
					{
						errors.enqueue(ParaCommon::PARAFRAME_ERROR::PLUGIN_LIB_CRITICAL_FUNCTION_NOT_RESOLVED);
					}

					if (iParaBase.getSupportedInterfaceVersions)
					{
						char* supportedInterfaceVersions;
						iParaBase.getSupportedInterfaceVersions(&supportedInterfaceVersions);
						std::string value{ supportedInterfaceVersions };
						delete supportedInterfaceVersions;

						PF_DEBUG(QString::fromStdString(value));
						success = true;
					}

					if (iParaBase.getPluginInterfaces)
					{
						char* pluginInterfaces;
						iParaBase.getPluginInterfaces(&pluginInterfaces);
						std::string value{ pluginInterfaces };
						delete pluginInterfaces;

						PF_DEBUG(QString::fromStdString(value));
						success = true;
					}

					if (iParaBase.setPluginEnabled_cb)
					{
						iParaBase.setPluginEnabled_cb(fnptr.test);
						//iParaBase.setPluginEnabled_cb(pluginEnabled_unbound);
						PF_DEBUG("setPluginEnabledCb resolved...");
						success = true;
					}

					

					if (iParaBase.pluginEnable)
					{
						int value = iParaBase.pluginEnable();
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

void ParaLib::ParaPlugin::pluginEnabled_bound(bool p_success, int p_value)
{
	xt = [=](int v) {};
	bool val = p_success;
	PF_DEBUG(QString("inside pluginEnabled (bound) with result of: " + QString(val ? "true" : "false")));
}

void ParaLib::pluginEnabled_unbound(bool p_success, int p_value)
{
	bool val = p_success;
	PF_DEBUG(QString("inside pluginEnabled (unbound) with result of: " + QString(val ? "true" : "false")));
}
