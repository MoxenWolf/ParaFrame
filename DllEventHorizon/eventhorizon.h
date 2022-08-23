#pragma once

#include "paraplugin_include.h"

#include <string>

namespace ParaPlugin
{
	class EventHorizon : public IParaBase
	{
		int pluginEnable()
		{
			return 43;
		}
	};


	/* *** ParaFrame Required *** */
	int pluginEnable()
	{
		int returnCode = 42;

		//implement pluginEnable

		return returnCode;
	}

	/* *** ParaFrame Required *** */
	PARAPLUGIN_EXPORT int pluginDisable()
	{
		int returnCode = 42;

		//implement pluginDisable

		return returnCode;
	}
}