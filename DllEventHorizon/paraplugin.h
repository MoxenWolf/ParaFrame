#pragma once

#include <string>
#include <list>


#define PARAPLUGIN_EXPORT extern "C" __declspec(dllexport)

namespace ParaPlugin
{
	const std::list<std::string> SUPPORTED_INTERFACE_VERSIONS{ "0.1a", };
	PARAPLUGIN_EXPORT const std::list<std::string> getSupportedInterfaceVersions()
	{
		return SUPPORTED_INTERFACE_VERSIONS;
	}
}