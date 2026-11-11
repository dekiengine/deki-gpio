#include "GpioPinSetup.h"
#include "DekiGPIO.h"

#include <deki/LogSystem.h>
#include <deki/Time.h>

namespace DekiGpio
{

void GpioPinSetup::Setup(SetupCallback onComplete)
{
    if (pin < 0)
    {
        if (onComplete)
        {
            onComplete(true);
        }
        return;
    }

    IDekiGPIO* gpio = DekiGPIO::GetCurrent();
    if (!gpio)
    {
        // The desktop, or a platform whose package has no pins: nothing to drive.
        DEKI_LOG_WARNING("GpioPinSetup: this platform has no GPIO backend; GPIO %d left alone", static_cast<int>(pin));
        if (onComplete)
        {
            onComplete(true);
        }
        return;
    }

    if (!gpio->SetOutput(pin, high))
    {
        DEKI_LOG_ERROR("GpioPinSetup: GPIO %d cannot be driven as an output", static_cast<int>(pin));
        if (onComplete)
        {
            onComplete(false);
        }
        return;
    }
    DEKI_LOG_INFO("GpioPinSetup: GPIO %d driven %s", static_cast<int>(pin), high ? "high" : "low");

    if (settleMs > 0)
    {
        Deki::Time::Delay(static_cast<uint32_t>(settleMs));
    }

    if (onComplete)
    {
        onComplete(true);
    }
}

}  // namespace DekiGpio
