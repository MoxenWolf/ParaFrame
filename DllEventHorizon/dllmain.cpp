// dllmain.cpp : Defines the entry point for the DLL application.
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>

#include "eventhorizon.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    int value = 0;

    switch (ul_reason_for_call)
    {
        
    case DLL_PROCESS_ATTACH:
        ParaPlugin::g_plugin = new ParaPlugin::EventHorizon;
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        if (ParaPlugin::g_plugin)
        {
            delete ParaPlugin::g_plugin;
        }
        break;
    }
    return TRUE;
}

