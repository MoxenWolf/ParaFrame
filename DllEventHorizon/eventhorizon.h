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

	const std::vector<std::string> INTERFACES{ "IParaBase, ISwitchable" };

	PARAPLUGIN_EXPORT void getInterfaces(char** out_interfaces)
	{
		std::string result = "";

	}

	PARAPLUGIN_EXPORT void getSupportedFunctions_translator(char ** out_supportedFunctions)
	{
		if (g_plugin)
		{
			/*std::string result = "";
			for (std::string value : g_plugin->SUPPORTED_FUNCTIONS)
			{
				result.append(value);
				result.append(",");
			}*/

			*out_supportedFunctions = translateStr(toJoinedStr(g_plugin->SUPPORTED_FUNCTIONS));
		}
	}

	PARAPLUGIN_EXPORT int pluginEnable_translator()
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

	PARAPLUGIN_EXPORT void setCbPluginEnabled_translator(void(*cb)())
	{
		if (g_plugin)
		{
			g_plugin->setPluginEnabledCb(cb);
		}
	}
}

