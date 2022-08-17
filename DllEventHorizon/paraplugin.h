#pragma once

#include <string>
#include <list>


#define PARAPLUGIN_EXPORT extern "C" __declspec(dllexport)

namespace ParaPlugin
{
	std::list<std::string> INTERFACE_VERSION{ "0.1a", };
	PARAPLUGIN_EXPORT std::list<std::string> getInterfaceVersion()
	{
		return INTERFACE_VERSION;
	}


	extern "C" __declspec(dllexport) int (*pluginEnableExport)() = 0;
	extern "C" __declspec(dllexport) int (*pluginDisableExport)() = 0;

}