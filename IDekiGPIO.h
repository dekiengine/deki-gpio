#pragma once

#include <cstdint>

namespace DekiGpio
{

enum class Pull : uint8_t
{
    None = 0,
    Up = 1,
    Down = 2
};

enum class Edge : uint8_t
{
    Rising = 0,
    Falling = 1,
    Both = 2
};

/**
 * @brief Digital pins, as a platform provides them
 *
 * Drive a pin, read a pin, and count a pin's edges by interrupt. The last is
 * what a device that pulses (a trackball, a rotary encoder, a flow meter)
 * needs: a game polls once a frame, and a fast roll puts several pulses in
 * one frame, so the count has to be kept between polls by the platform.
 *
 * Pin numbers are the platform's own. The platform package (deki-esp32-
 * integration for ESP-IDF) registers its implementation with DekiGPIO.
 */
class IDekiGPIO
{
public:
    virtual ~IDekiGPIO() = default;

    virtual bool SetOutput(int pin, bool high) = 0;
    virtual bool SetInput(int pin, Pull pull) = 0;
    virtual bool Write(int pin, bool high) = 0;
    /// False when the pin is low, not configured, or not an input.
    virtual bool Read(int pin) = 0;

    /// Make `pin` an input with `pull` and count its edges from now on.
    virtual bool CountEdges(int pin, Edge edge, Pull pull) = 0;
    /// Edges counted since the last call; 0 for a pin not being counted.
    virtual uint32_t TakeEdges(int pin) = 0;
    virtual void StopCounting(int pin) = 0;
};

}  // namespace DekiGpio
