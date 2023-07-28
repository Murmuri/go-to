#include <Config.h>
#include <RtcDS1302.h>
#include <ThreeWire.h>

ThreeWire myWire(WATCH_DAT_PIN, WATCH_CLK_PIN, WATCH_RST_PIN);
RtcDS1302<ThreeWire> Rtc(myWire);

class Watch
{
public:
  Watch()
  {
    Serial.print("Data: ");
    Serial.println(__DATE__);
    Serial.print("Time: ");
    Serial.println(__TIME__);

    Rtc.Begin();
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    Rtc.SetDateTime(compiled);
    Serial.println("Watch module initialized");
  }

  long getStarUnixTime()
  {
    Rtc.GetDateTime();
    RtcDateTime now = Rtc.GetDateTime();
    long nowEarthUnixTime = now.Unix32Time() - (LOCAL_TIME * 60 * 60); // now time
    long pastEarthTime = nowEarthUnixTime - EARTH_TIME;
    long pastStarTime = pastEarthTime / STAR_DAY_COEFFICIENT;
    long starTime = STAR_TIME + pastStarTime;
    return starTime % (24*60*60);
  }

  long getRAStarTime(long mountTime) {
    long time = getStarUnixTime();
    long mountStarTime = time - mountTime;
    return mountStarTime % (24*60*60);
  }
};