#pragma once

//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
//// Windows Header Files
//#include <windows.h>

#include <string>
#include <list>

#ifdef PF_EXPORTING
#define PARAPLUGIN_EXPORT extern "C" __declspec(dllexport)
#else
#define PARAPLUGIN_EXPORT /*__declspect(dllimport)*/
#endif

/* *** stored in paraplugin.h *** */

namespace ParaPlugin
{
	std::list<std::string> INTERFACE_VERSION{ "0.1a", };
	/*PARAPLUGIN_EXPORT int (*pluginEnableExtern)();
	PARAPLUGIN_EXPORT int (*pluginDisableExtern)();*/
	
}

