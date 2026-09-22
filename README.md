# Deki GPIO

Digital pins for the Deki Engine: drive a pin, read a pin, and count a pin's edges by interrupt. The last is for devices that pulse - a trackball, a rotary encoder - which a game polling once a frame would otherwise miss steps from.

This package is the interface. The platform package supplies the pins: `deki-esp32-integration` for ESP-IDF. On the desktop there is no backend and `DekiGPIO::GetCurrent()` is null.

Part of [Deki Engine](https://github.com/dekiengine/deki-engine).

## Use

```cpp
#include "DekiGPIO.h"  // from deki-gpio

if (auto* gpio = DekiGpio::DekiGPIO::GetCurrent())
{
    gpio->CountEdges(3, DekiGpio::Edge::Falling, DekiGpio::Pull::Up);
    // each frame:
    uint32_t steps = gpio->TakeEdges(3);
}
```

`deki-input`'s trackball is the first user.

## Boot pins

`GpioPinSetup` drives one pin high or low during boot, with an optional wait
afterwards. Boards gate things behind a pin: the rail feeding the display, or
the chip select of another device on the display's SPI bus. Add one per pin to
the platform's boot scene and list it in `setupComponents` ahead of the step
that needs it.

## Install

Package Manager in the Deki Editor, or `DekiEditor --packages-add deki-gpio <project>`.

## Dependencies

None.

## License

Apache 2.0. See [LICENSE](LICENSE).
