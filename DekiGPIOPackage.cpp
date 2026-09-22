/**
 * @file DekiGPIOPackage.cpp
 * @brief Package entry point for deki-gpio
 */
#include "DekiGPIOPackage.h"
#include <deki/interop/Plugin.h>
#include <deki/LogSystem.h>

extern void DekiGPIO_RegisterComponents();
extern int  DekiGPIO_GetAutoComponentCount();
extern const Deki::ComponentMeta* DekiGPIO_GetAutoComponentMeta(int index);

namespace DekiGpio
{

#ifdef DEKI_EDITOR
#endif

static bool s_GPIORegistered = false;


}  // namespace DekiGpio
// The exports below are C symbols at global scope; the package's own
// registration helpers and statics live in its namespace.
using namespace DekiGpio;

extern "C" {

DEKI_GPIO_API int DekiGPIO_EnsureRegistered(void)
{
#ifdef DEKI_EDITOR
    if (s_GPIORegistered) return ::DekiGPIO_GetAutoComponentCount();
    s_GPIORegistered = true;
    ::DekiGPIO_RegisterComponents();
    return ::DekiGPIO_GetAutoComponentCount();
#else
    return 0;
#endif
}

DEKI_PLUGIN_API const char* DekiPlugin_GetName(void)    { return "Deki GPIO Package"; }
DEKI_PLUGIN_API const char* DekiPlugin_GetVersion(void)
{
#ifdef DEKI_PACKAGE_VERSION
    return DEKI_PACKAGE_VERSION;
#else
    return "0.0.0-dev";
#endif
}
DEKI_PLUGIN_API int  DekiPlugin_Init(void)     { DEKI_LOG_INFO("[deki-gpio] DekiPlugin_Init"); return 0; }
DEKI_PLUGIN_API void DekiPlugin_Shutdown(void) { s_GPIORegistered = false; }

#ifdef DEKI_EDITOR
DEKI_PLUGIN_API int  DekiPlugin_GetComponentCount(void) { return ::DekiGPIO_GetAutoComponentCount(); }
DEKI_PLUGIN_API const Deki::ComponentMeta* DekiPlugin_GetComponentMeta(int index)
{
    return ::DekiGPIO_GetAutoComponentMeta(index);
}
#else
DEKI_PLUGIN_API int  DekiPlugin_GetComponentCount(void) { return 0; }
DEKI_PLUGIN_API const Deki::ComponentMeta* DekiPlugin_GetComponentMeta(int) { return nullptr; }
#endif

DEKI_PLUGIN_API void DekiPlugin_RegisterComponents(void)
{
#ifdef DEKI_EDITOR
    int n = DekiGPIO_EnsureRegistered();
    DEKI_LOG_INFO("[deki-gpio] ::DekiPlugin_RegisterComponents -> %d component(s)", n);
#endif
}


}  // extern "C"

