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

		int pluginEnable() //TODO Change from returning int to void
		{
			//do stuff to enable plugin

			pluginEnabled(); //call to plugin manager
			return 43;
		}
	};

	/* *** DO NOT ALTER BELOW *** */

	EventHorizon* g_plugin = nullptr;

	const std::vector<std::string> PLUGIN_INTERFACES{ "IParaBase", "ISwitchable" };

	PARAPLUGIN_EXPORT void getPluginInterfaces_ex(char** out_interfaces)
	{
		*out_interfaces = translateStr(toJoinedStr(PLUGIN_INTERFACES));
	}

	PARAPLUGIN_EXPORT int pluginEnable_ex()
	{
		if (g_plugin)
		{	
			int value = g_plugin->pluginEnable(); //example calls pluginEnabled() from inside this f()
			
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

