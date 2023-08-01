#include <RtcDS1302.h>
#include <ThreeWire.h>

int WATCH_CLK_PIN = 6;
int WATCH_DAT_PIN = 7;
int WATCH_RST_PIN = 8;
int LOCAL_TIME = 3;
long EARTH_TIME = 1689903317; // 21.07.24 1:35:17 utc
long STAR_TIME = 1689897600;  // 21.07.24 00:00:00 utc
double STAR_DAY_COEFFICIENT = 0.99726956643518518519;

ThreeWire myWire(WATCH_DAT_PIN, WATCH_CLK_PIN, WATCH_RST_PIN);
RtcDS1302<ThreeWire> Rtc(myWire);

class Watch
{
public:
  Watch()
  {
    Rtc.Begin();
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    Rtc.SetDateTime(compiled);
    Serial.println("WATCH MODULE: initialization finished");
  }

  long getStarUnixTime()
  {
    Rtc.GetDateTime();
    RtcDateTime now = Rtc.GetDateTime();
    long nowEarthUnixTime = now.Unix32Time() - (LOCAL_TIME * 60 * 60);
    long pastEarthTime = nowEarthUnixTime - EARTH_TIME;
    long pastStarTime = pastEarthTime / STAR_DAY_COEFFICIENT;
    long starTime = STAR_TIME + pastStarTime;
    return starTime % (24 * 60 * 60);
  }

  long getRAStarTime(long mountTime)
  {
    long time = getStarUnixTime();
    long mountStarTime = time - mountTime;
    return mountStarTime % (24 * 60 * 60);
  }
};