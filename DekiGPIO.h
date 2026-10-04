#pragma once

#include "IDekiGPIO.h"
#include "DekiGPIOPackage.h"

namespace DekiGpio
{

/// The platform's pins. Each platform's package registers one implementation
/// at start-up, and components reach it through GetCurrent(). Null on a
/// platform without pins, such as the desktop.
class DEKI_GPIO_API DekiGPIO
{
public:
    static void SetCurrent(IDekiGPIO* gpio);
    static IDekiGPIO* GetCurrent();

private:
    static IDekiGPIO* s_Current;
};

}  // namespace DekiGpio
