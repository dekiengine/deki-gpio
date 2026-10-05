#pragma once

#include <cstdint>
#include <deki/SetupComponent.h>
#include <deki/reflection/Property.h>
#include "DekiGPIOPackage.h"

namespace DekiGpio
{

/// Drives one pin to a fixed level during boot.
///
/// Boards put things behind a pin: a power rail for the display and touch
/// controller, the chip select of a second device on the display's SPI bus, an
/// amplifier's enable. The pin must be at its level before the setup step that
/// needs it, so this is a setup step of its own: list it in
/// PlatformSetupComponent's setupComponents ahead of that step.
///
/// One pin per component; a board that needs three adds three. Works on any
/// platform whose package provides deki-gpio's backend.
DEKI_CATEGORY("GPIO")
DEKI_DISPLAY_NAME("GPIO Pin")
DEKI_DESCRIPTION(
    "Drives a pin high or low at boot: a power enable, or the chip select of an unused device on a shared bus.")
class DEKI_GPIO_API GpioPinSetup : public Deki::SetupComponent
{
public:
    DEKI_EXPORT
    DEKI_TOOLTIP("Pin number, as the platform numbers them (-1 = do nothing)")
    DEKI_RANGE(-1, 255)
    int32_t pin = -1;

    DEKI_EXPORT
    DEKI_TOOLTIP("Drive the pin high (off = low)")
    bool high = true;

    DEKI_EXPORT
    DEKI_TOOLTIP("Milliseconds to wait afterwards, for a power rail to come up before the next setup step")
    DEKI_RANGE(0, 5000)
    int32_t settleMs = 0;

    void Setup(SetupCallback onComplete) override;
    const char* GetSetupName() const override { return "GPIO Pin"; }
};

}  // namespace DekiGpio
