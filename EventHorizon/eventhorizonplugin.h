#pragma once

#include "paraplugin.h"

#include <string>

/* *** stored in their generated header *** */

namespace ParaPlugin
{
	/* *** pluginEnable ***
	/* [REQUIRED]
	*/
	PARAPLUGIN_EXPORT int pluginEnable()
	{
		int returnCode = 42;

		//implement pluginEnable

		return returnCode;
	}

	/* *** pluginDisable ***
	* [REQUIRED]
	*/
	PARAPLUGIN_EXPORT int pluginDisable()
	{
		int returnCode = 42;

		//implement pluginDisable

		return returnCode;
	}
}

// class PARAPLUGIN_EXPORT EventHorizon : virtual public ParaPlugin
//{
//public:
//	EventHorizon();
//	~EventHorizon();
//	void deviceStartup() const override;
//	void deviceShutdown() const override;
//protected:
//private:
//};
//
// extern "C" PARAPLUGIN_EXPORT ParaPlugin * createPlugin()
// {
//	 return new EventHorizon();
// }


//old...

//class PF_EXPORT EventHorizonPlugin
//{
//public:
//	EventHorizonPlugin();
//	~EventHorizonPlugin() = default;
//protected:
//private:
//};
//
//extern "C" __declspec(dllexport) void doEmpty();
//extern "C" __declspec(dllexport) void doInt(int);
//extern "C" __declspec(dllexport) int incInt(int);
//void doString(std::string);
//std::string retString(std::string);



/**
* export interface only with all pure virtual functions
* class then inherits from interface
* https://stackoverflow.com/questions/26234327/qlibrary-import-a-class
* */

