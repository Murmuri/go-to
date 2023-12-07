#include <RtcDS1302.h>
#include <ThreeWire.h>
#include "../config.h"

ThreeWire myWire(WATCH_DAT_PIN, WATCH_CLK_PIN, WATCH_RST_PIN);
RtcDS1302<ThreeWire> Rtc(myWire);

class Clock
{
  public:
    void initialize()
    long getStarUnixTime()
    long getRAStarTime(long mountTime)
};