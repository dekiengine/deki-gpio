#include "DekiGPIO.h"
#include <deki/LogSystem.h>

namespace DekiGpio
{

IDekiGPIO* DekiGPIO::s_Current = nullptr;

void DekiGPIO::SetCurrent(IDekiGPIO* gpio)
{
    s_Current = gpio;
    DEKI_LOG_INTERNAL("DekiGPIO: backend %s", gpio ? "registered" : "cleared");
}

IDekiGPIO* DekiGPIO::GetCurrent()
{
    return s_Current;
}

}  // namespace DekiGpio
