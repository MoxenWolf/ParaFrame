#pragma once

#include "paraplugin.h"

#include <string>

namespace ParaPlugin
{
	/* *** ParaFrame Required *** */
	PARAPLUGIN_EXPORT int pluginEnable()
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