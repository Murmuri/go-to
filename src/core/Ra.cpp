#include "Ra.h"

void Ra::initialize()
{
  setRpm(RA_DEFAULT_RPM);
  raTime = _clock.getRAStarTime(currentMountPosition);

  Serial.println("RA MODULE: initialization finished");
}

void Ra::update()
{
  if (parking)
  {
    return;
  }

  currentMountPositionStarTime = _clock.getRAStarTime(currentMountPosition);

  if (raTime != currentMountPositionStarTime)
  {
    Serial.println("RA MODULE: change coordinate");
    long secondsForMove = raTime - currentMountPositionStarTime;
    realMountPosition = receiveTopSidePosition(currentMountPosition);
    currentMountPosition = receiveCurrentMountPosition(currentMountPosition, secondsForMove);
    long realToGoPosition = receiveTopSidePosition(currentMountPosition);
    secondsForMove = getModulePosition(realToGoPosition) - getModulePosition(realToGoPosition);
    long steps = getStepsToMove(secondsForMove);
    move(steps);
    realMountPosition = realToGoPosition;
  }
}

void Ra::setRpm(int rpm)
{
  raStepper.setSpeed(rpm);
}

void Ra::setCoordinates(int h, int m, int s)
{
  raTime = getHoursInSeconds(h, m, s);
}

int Ra::getSide()
{
  if (currentMountPosition >= 6 * HOURS_IN_SEC && currentMountPosition < 18 * HOURS_IN_SEC)
  {
    return NEGATIVE_SIDE;
  }

  return POSITIVE_SIDES;
}

void Ra::setParking(bool p)
{
  parking = p;
}

long Ra::receiveTopSidePosition(long position)
{
  if (position >= 6 * HOURS_IN_SEC && position < 18 * HOURS_IN_SEC)
  {
    return (position + (12 * HOURS_IN_SEC)) % (24 * HOURS_IN_SEC)
  }

  return position;
}

long Ra::receiveCurrentMountPosition(long position, long seconds)
{
  if (position + seconds >= 0)
  {
    return (position + seconds) % (24 * HOURS_IN_SEC);
  }

  return (24 * HOURS_IN_SEC) + (position + seconds);
}

long Ra::getHoursInSeconds(int hour, int min, int sec)
{
  return ((((long)hour * 60) + min) * 60) + sec;
}

long Ra::getStepsToMove(int sec)
{
  return sec / secondsPerStep;
}

long Ra::getModulePosition(long position)
{
  if (position >= 18 * HOURS_IN_SEC && position < 24 * HOURS_IN_SEC)
  {
    return position - 18 * HOURS_IN_SEC;
  }

  return position + 6 * HOURS_IN_SEC;
}

void Ra::move(long steps)
{
  Serial.println("RA MODULE: move move...");
  int index = abs(steps / HOURS_IN_SEC);
  int remainderSteps = steps % HOURS_IN_SEC;

  while (index > 0)
  {
    raStepper.step(HOURS_IN_SEC);
    index--;
  }

  raStepper.step(remainderSteps);
  Serial.println("RA MODULE: move over");
}
