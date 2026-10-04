/**
 * @file DekiGPIOPackage.cpp
 * @brief Package entry point for deki-gpio
 */
#include "DekiGPIOPackage.h"
#include <deki/interop/Plugin.h>
#include <deki/LogSystem.h>

extern void DekiGPIORegisterComponents();
extern int DekiGPIOGetAutoComponentCount();
extern const Deki::ComponentMeta* DekiGPIOGetAutoComponentMeta(int index);

namespace DekiGpio
{

#ifdef DEKI_EDITOR
#endif

static bool s_GPIORegistered = false;

}  // namespace DekiGpio
// The exports below are C symbols at global scope; the package's own
// registration helpers and statics live in its namespace.
using namespace DekiGpio;

extern "C"
{
    DEKI_GPIO_API int DekiGPIOEnsureRegistered(void)
    {
#ifdef DEKI_EDITOR
        if (s_GPIORegistered)
        {
            return ::DekiGPIOGetAutoComponentCount();
        }
        s_GPIORegistered = true;
        ::DekiGPIORegisterComponents();
        return ::DekiGPIOGetAutoComponentCount();
#else
        return 0;
#endif
    }

    DEKI_PLUGIN_API const char* DekiPluginGetName(void)
    {
        return "Deki GPIO Package";
    }
    DEKI_PLUGIN_API const char* DekiPluginGetVersion(void)
    {
#ifdef DEKI_PACKAGE_VERSION
        return DEKI_PACKAGE_VERSION;
#else
        return "0.0.0-dev";
#endif
    }
    DEKI_PLUGIN_API int DekiPluginInit(void)
    {
        return 0;
    }
    DEKI_PLUGIN_API void DekiPluginShutdown(void)
    {
        s_GPIORegistered = false;
    }

#ifdef DEKI_EDITOR
    DEKI_PLUGIN_API int DekiPluginGetComponentCount(void)
    {
        return ::DekiGPIOGetAutoComponentCount();
    }
    DEKI_PLUGIN_API const Deki::ComponentMeta* DekiPluginGetComponentMeta(int index)
    {
        return ::DekiGPIOGetAutoComponentMeta(index);
    }
#else
    DEKI_PLUGIN_API int DekiPluginGetComponentCount(void)
    {
        return 0;
    }
    DEKI_PLUGIN_API const Deki::ComponentMeta* DekiPluginGetComponentMeta(int)
    {
        return nullptr;
    }
#endif

    DEKI_PLUGIN_API void DekiPluginRegisterComponents(void)
    {
#ifdef DEKI_EDITOR
        DekiGPIOEnsureRegistered();
#endif
    }

}  // extern "C"
