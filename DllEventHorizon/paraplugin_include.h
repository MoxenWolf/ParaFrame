#pragma once

#include <string>
#include <vector>


#define PARAPLUGIN_EXPORT extern "C" __declspec(dllexport)

typedef int (*pluginEnabled)();


namespace ParaPlugin
{
	class IParaBase
	{
	public:
		const std::vector<std::string> SUPPORTED_INTERFACE_VERSIONS{ "0.1a", };
		const std::vector<std::string> SUPPORTED_FUNCTIONS{ "getSupportedFunctions_translator", "pluginEnable_translator" };

		std::vector<std::string> getSupportedFunctions()
		{
			return std::vector<std::string>{"pluginEnable_translator"};
		}

		void(*pluginEnabled)() = nullptr;

		void setPluginEnabledCb(void(*callback)())
		{
			pluginEnabled = callback;
		}

		virtual int pluginEnable() = 0;
	};
}