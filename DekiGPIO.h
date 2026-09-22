#pragma once

#include "IDekiGPIO.h"
#include "DekiGPIOPackage.h"

namespace DekiGpio
{

/**
 * @brief The platform's pins
 *
 * One implementation per platform, registered by its package at start-up;
 * components reach it through GetCurrent(). Null on a platform with no
 * pins to speak of, such as the desktop.
 */
class DEKI_GPIO_API DekiGPIO
{
public:
    static void SetCurrent(IDekiGPIO* gpio);
    static IDekiGPIO* GetCurrent();

private:
    static IDekiGPIO* s_Current;
};

}  // namespace DekiGpio
