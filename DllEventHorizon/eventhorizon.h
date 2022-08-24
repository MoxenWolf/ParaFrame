#pragma once

#include "paraplugin_include.h"

#include <string>

namespace ParaPlugin
{
	class EventHorizon : public IParaBase
	{
	public:
		EventHorizon()
		{
			//perform any needed plugin init...
		}
		~EventHorizon() {}

		int pluginEnable()
		{
			return 43;
		}
	};

	/* *** DO NOT ALTER BELOW *** */

	EventHorizon* g_plugin;

	PARAPLUGIN_EXPORT void getSupportedFunctions_translator(char ** out_supportedFunctions)
	{
		std::string result = "";
		for (std::string value : g_plugin->SUPPORTED_FUNCTIONS)
		{
			result.append(value);
			result.append(",");
		}
		
		*out_supportedFunctions = _strdup(result.c_str());
	}

	PARAPLUGIN_EXPORT int pluginEnable_translator()
	{
		if (g_plugin)
		{
			
			int value = g_plugin->pluginEnable();
			return value;
		}
	}
}

