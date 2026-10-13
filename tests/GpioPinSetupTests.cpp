// GpioPinSetup drives one pin at boot (a power rail, a backlight, a chip's
// enable) before the components that need it start. What it does without a
// pin, without a GPIO backend, and when the pin refuses, decides whether a
// board boots, so each case is pinned here.

#include <gtest/gtest.h>

#include "DekiGPIO.h"
#include "GpioPinSetup.h"

#include <deki/Time.h>

#include <vector>

using namespace DekiGpio;

namespace
{

class FakeGPIO : public IDekiGPIO
{
public:
    struct Call
    {
        int pin;
        bool high;
    };
    std::vector<Call> outputs;
    bool refuse = false;

    bool SetOutput(int pin, bool high) override
    {
        if (refuse)
        {
            return false;
        }
        outputs.push_back({ pin, high });
        return true;
    }
    bool SetInput(int, Pull) override { return true; }
    bool Write(int, bool) override { return true; }
    bool Read(int) override { return false; }
    bool CountEdges(int, Edge, Pull) override { return true; }
    uint32_t TakeEdges(int) override { return 0; }
    void StopCounting(int) override {}
};

class GpioPinSetupTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        DekiGPIO::SetCurrent(&gpio);
        delays.clear();
        Deki::Time::SetDelayFunction([this](uint32_t ms) { delays.push_back(ms); });
    }
    void TearDown() override
    {
        DekiGPIO::SetCurrent(nullptr);
        Deki::Time::SetDelayFunction(nullptr);
    }

    static bool RunSetup(GpioPinSetup& s)
    {
        bool reported = false;
        s.Setup([&](bool ok) { reported = ok; });
        return reported;
    }

    FakeGPIO gpio;
    std::vector<uint32_t> delays;
};

}  // namespace

TEST_F(GpioPinSetupTest, DrivesThePinAndWaitsForItToSettle)
{
    GpioPinSetup s;
    s.pin = 10;
    s.high = false;
    s.settleMs = 50;
    EXPECT_TRUE(RunSetup(s));
    ASSERT_EQ(gpio.outputs.size(), 1u);
    EXPECT_EQ(gpio.outputs[0].pin, 10);
    EXPECT_FALSE(gpio.outputs[0].high);
    EXPECT_EQ(delays, std::vector<uint32_t>{ 50 });
}

TEST_F(GpioPinSetupTest, NoSettleTimeMeansNoWait)
{
    GpioPinSetup s;
    s.pin = 3;
    EXPECT_TRUE(RunSetup(s));
    EXPECT_TRUE(gpio.outputs[0].high);  // high by default
    EXPECT_TRUE(delays.empty());
}

TEST_F(GpioPinSetupTest, NoPinDoesNothingAndSucceeds)
{
    GpioPinSetup s;  // pin -1
    EXPECT_TRUE(RunSetup(s));
    EXPECT_TRUE(gpio.outputs.empty());
}

TEST_F(GpioPinSetupTest, NoBackendIsNotAFailure)
{
    // The desktop simulator has no pins; a boot scene made for a board must
    // still boot there.
    DekiGPIO::SetCurrent(nullptr);
    GpioPinSetup s;
    s.pin = 10;
    EXPECT_TRUE(RunSetup(s));
}

TEST_F(GpioPinSetupTest, APinThatCannotBeAnOutputFailsTheBoot)
{
    gpio.refuse = true;
    GpioPinSetup s;
    s.pin = 45;
    s.settleMs = 100;
    EXPECT_FALSE(RunSetup(s));
    EXPECT_TRUE(delays.empty());
}
