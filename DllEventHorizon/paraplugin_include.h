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
		std::vector<std::string> getSupportedFunctions()
		{
			return std::vector<std::string>{"pluginEnable_translator"};
		}

		virtual int pluginEnable() = 0;
	};

	/*PARAPLUGIN_EXPORT class IParaBase
	{
	public:
		std::vector<std::string> getSupportedFunctions()
		{
			return std::vector<std::string>{"pluginEnable_translator"};
		}

		virtual int pluginEnable() = 0;
	};*/

	

	/*typedef class EventHorizon : public IParaBase;
	extern class EventHorzon : public IParaBase {};*/
	//extern class EventHorizon : public IParaBase {};
	//EventHorizon* g_plugin = nullptr;

	
	
	////legacy ...

	//const std::vector<std::string> SUPPORTED_INTERFACE_VERSIONS{ "0.1a", };
	/*PARAPLUGIN_EXPORT const std::list<std::string> getSupportedInterfaceVersions()
	{
		return SUPPORTED_INTERFACE_VERSIONS;
	}*/

	/*PARAPLUGIN_EXPORT const std::vector<std::string> getSupportedFunctions()
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
	}*/
}