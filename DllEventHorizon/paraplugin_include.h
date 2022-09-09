#pragma once

#include <string>
#include <vector>


#define PARAPLUGIN_EXPORT extern "C" __declspec(dllexport)

typedef int (*pluginEnabled)();


namespace ParaPlugin
{
	class IParaBase //TODO: probably change to struct and put in a virtual destructor
	{
	public:
		const std::vector<std::string> SUPPORTED_INTERFACE_VERSIONS{ "0.1a", };
		const std::vector<std::string> SUPPORTED_FUNCTIONS{ "getSupportedFunctions_translator", "pluginEnable_translator" };

		int pluginId{0};

		std::vector<std::string> getSupportedFunctions()
		{
			return std::vector<std::string>{"pluginEnable_translator"};
		}

		void(*pluginEnabled)() = nullptr;

		void setPluginEnabledCb(void(*callback)())
		{
			pluginEnabled = callback;
		}
		
		void setPluginId(int id)
		{
			pluginId = id;
		}

		virtual int pluginEnable() = 0;
	};

	struct ICamera
	{

	};

	
}