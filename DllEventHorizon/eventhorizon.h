#pragma once

#include "paraplugin_include.h"

#include <string>

namespace ParaPlugin
{
	class EventHorizon : public IParaBase, public ISwitchable
	{
	public:
		EventHorizon()
		{
			//perform any needed plugin init...
		}
		~EventHorizon() {}

		int pluginEnable()
		{
			//do stuff to enable plugin

			pluginEnabled(); //call to plugin manager
			return 43;
		}
	};

	/* *** DO NOT ALTER BELOW *** */

	EventHorizon* g_plugin = nullptr;

	const std::vector<std::string> PLUGIN_INTERFACES{ "IParaBase", "ISwitchable" };

	PARAPLUGIN_EXPORT void getInterfaces_ex(char** out_interfaces)
	{
		*out_interfaces = translateStr(toJoinedStr(PLUGIN_INTERFACES));
	}

	/*PARAPLUGIN_EXPORT void getSupportedFunctions_translator(char ** out_supportedFunctions)
	{
		if (g_plugin)
		{
			*out_supportedFunctions = translateStr(toJoinedStr(g_plugin->SUPPORTED_FUNCTIONS));
		}
	}*/

	PARAPLUGIN_EXPORT int pluginEnable_ex()
	{
		if (g_plugin)
		{	
			int value = g_plugin->pluginEnable();
			/*if (value > 0 && g_plugin->pluginEnabled)
			{
				g_plugin->pluginEnabled();
			}*/
			return value;
		}
	}

	PARAPLUGIN_EXPORT void setCbPluginEnabled_ex(void(*cb)())
	{
		if (g_plugin)
		{
			g_plugin->setPluginEnabledCb(cb);
		}
	}
}

