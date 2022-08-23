#pragma once

#include <string>
#include <vector>


#define PARAPLUGIN_EXPORT extern "C" __declspec(dllexport)

typedef int (*pluginEnabled)();

namespace ParaPlugin
{
	const std::vector<std::string> SUPPORTED_INTERFACE_VERSIONS{ "0.1a", };
	/*PARAPLUGIN_EXPORT const std::list<std::string> getSupportedInterfaceVersions()
	{
		return SUPPORTED_INTERFACE_VERSIONS;
	}*/

	PARAPLUGIN_EXPORT const std::vector<std::string> getSupportedFunctions()
	{
		return std::vector<std::string>{"pluginEnable_translator"};
	}

	int pluginEnable();

	PARAPLUGIN_EXPORT int pluginEnable_translator()
	{
		if (pluginEnable)
		{
			return pluginEnable();
		}
		else
		{
			return -1;
		}
	}
}