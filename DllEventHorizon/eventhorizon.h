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
			//
		}
		~EventHorizon() {}

		int pluginEnable()
		{
			return 43;
		}
	};
}

namespace externed
{
	extern ParaPlugin::EventHorizon* g_plugin;
}

namespace ParaPlugin
{
	/* *** DO NOT ALTER BELOW *** */

	

	PARAPLUGIN_EXPORT int pluginEnable_translator()
	{
		if (externed::g_plugin)
		{
			
			int value = externed::g_plugin->pluginEnable();
			return value;
		}
	}

	//legacy ...

	/* *** ParaFrame Required *** */
	//int pluginEnable()
	//{
	//	int returnCode = 42;

	//	//implement pluginEnable

	//	return returnCode;
	//}

	///* *** ParaFrame Required *** */
	//PARAPLUGIN_EXPORT int pluginDisable()
	//{
	//	int returnCode = 42;

	//	//implement pluginDisable

	//	return returnCode;
	//}
}

