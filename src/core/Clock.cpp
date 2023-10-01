void Clock::initialize()
{
  Rtc.Begin();
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  Rtc.SetDateTime(compiled);
  Serial.println("WATCH MODULE: initialization finished");
}

long Clock::getStarUnixTime()
{
  Rtc.GetDateTime();
  RtcDateTime now = Rtc.GetDateTime();
  long nowEarthUnixTime = now.Unix32Time() - (LOCAL_TIME * 60 * 60);
  long pastEarthTime = nowEarthUnixTime - EARTH_TIME;
  long pastStarTime = pastEarthTime / STAR_DAY_COEFFICIENT;
  long starTime = STAR_TIME + pastStarTime;
  return starTime % (24 * 60 * 60);
}

long Clock::getRAStarTime(long mountTime)
{
  long time = getStarUnixTime();
  long mountStarTime = time - mountTime;
  return mountStarTime % (24 * 60 * 60);
}
