#pragma once

#include "paraplugin_include.h"

#include <string>

namespace ParaPlugin
{
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