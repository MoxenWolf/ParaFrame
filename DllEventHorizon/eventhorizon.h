#pragma once

#include "paraplugin_include.h"

#include <string>
#include <iostream>

namespace ParaPlugin
{
	class EventHorizon : public IParaBase, ICalibratable, IGenericSensor
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

			OutputDebugString(L"inside before...\n");
			bool val = false;
			pluginEnabled(true, 42); //call to plugin manager
			OutputDebugString(L"inside mid...\n");
			bool val2 = true;
			pluginEnabled(false, 43);
			OutputDebugString(L"inside after...\n");

			
			return 43;
		}

		bool calibrate()
		{

		}

		float getSensorValue()
		{

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
		int rtv = -1;

		if (g_plugin)
		{	
			rtv = g_plugin->pluginEnable(); //example calls pluginEnabled() from inside this f()
		}
		return rtv;
	}

	PARAPLUGIN_EXPORT void setCbPluginEnabled_ex(ft_void_bool cb) //TODO Change to respect new typedefs
	{
		if (g_plugin)
		{
			g_plugin->setPluginEnabledCb(cb);
		}
	}
}

