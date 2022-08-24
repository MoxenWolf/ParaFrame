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

	PARAPLUGIN_EXPORT int pluginEnable_translator()
	{
		if (g_plugin)
		{
			
			int value = g_plugin->pluginEnable();
			return value;
		}
	}
}

