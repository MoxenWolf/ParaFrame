#pragma once

#include <string>
#include <vector>


#define PARAPLUGIN_EXPORT extern "C" __declspec(dllexport)

typedef int (*pluginEnabled)();


namespace ParaPlugin
{
	struct IParaBase //TODO: probably change to struct and put in a virtual destructor
	{
	public:
		IParaBase() = default;
		virtual ~IParaBase() = default;

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

	struct ISwitchable
	{
		ISwitchable() = default;
		virtual ~ISwitchable() = default;

		
	};

	/* *** Helper f()s and vals *** */

	const char LIST_SEP = '#';

	template <typename T> std::string toJoinedStr(T v)
	{
		std::string r;
		for (std::string s : v)
		{
			r.append(s);
			r.append(&LIST_SEP);
		}

		return (r.back() == LIST_SEP) ? r.substr(0, r.length() - 1) : r;
	}

	char* translateStr(std::string p_sValue)
	{
		unsigned long long size = strlen(p_sValue.c_str()) + 1;
		char* x = new char[size]; //deleted in reading function, sorry for the mess but needed an out param for compat
		strcpy_s(x, size, p_sValue.c_str());
		return x;
	}
	
}