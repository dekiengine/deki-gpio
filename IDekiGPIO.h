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

/// Digital pins, as a platform provides them: drive a pin, read a pin, and
/// count a pin's edges by interrupt.
///
/// Edge counting is for devices that pulse (a trackball, a rotary encoder, a
/// flow meter). A game polls once a frame and a fast roll puts several pulses
/// in one frame, so the platform keeps the count between polls.
///
/// Waiting for an edge is for a signal that must be acted on at once, such
/// as a panel's tearing-effect line, which says the panel has started a new
/// refresh.
///
/// Pin numbers are the platform's own. The platform package (deki-esp32-
/// integration for ESP-IDF) registers its implementation with DekiGPIO.
class IDekiGPIO
{
public:
    virtual ~IDekiGPIO() = default;

    virtual bool SetOutput(int pin, bool high) = 0;
    virtual bool SetInput(int pin, Pull pull) = 0;
    virtual bool Write(int pin, bool high) = 0;
    /// False when the pin is low, not configured, or not an input.
    virtual bool Read(int pin) = 0;

    /// Makes `pin` an input with `pull` and count its edges from now on.
    virtual bool CountEdges(int pin, Edge edge, Pull pull) = 0;
    /// Edges counted since the last call; 0 for a pin not being counted.
    virtual uint32_t TakeEdges(int pin) = 0;
    virtual void StopCounting(int pin) = 0;

    /// Blocks until `pin`, counted with CountEdges, sees its next edge, or
    /// `timeoutMs` passes; it returns within an interrupt's latency of the
    /// edge. An edge before the call does not end the wait. One task waits on
    /// a pin at a time. False on a timeout, for a pin not being counted, or
    /// on a platform that cannot wait (the default).
    virtual bool WaitForEdge(int pin, uint32_t timeoutMs)
    {
        (void)pin;
        (void)timeoutMs;
        return false;
    }
};

}  // namespace DekiGpio
