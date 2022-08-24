// dllmain.cpp : Defines the entry point for the DLL application.
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>

#include "eventhorizon.h"

namespace externed
{
    ParaPlugin::EventHorizon* g_plugin;
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    int value = 0;

    switch (ul_reason_for_call)
    {
        
    case DLL_PROCESS_ATTACH:
        OutputDebugString(L"\nAttaching...\n");
        externed::g_plugin = new ParaPlugin::EventHorizon;
        value = externed::g_plugin->pluginEnable();
        OutputDebugString(L"\n...after value assinment\n");
        break;
    case DLL_THREAD_ATTACH:
        
        break;
    case DLL_THREAD_DETACH:
        
        break;
    case DLL_PROCESS_DETACH:
        if (externed::g_plugin)
        {
            OutputDebugString(L"\n...detaching...\n");
            delete externed::g_plugin;
            externed::g_plugin = nullptr;
        }
        break;
    }
    return TRUE;
}

