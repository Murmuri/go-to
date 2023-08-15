#include <Stepper.h>
#include <Watch.h>

int RA_DIRECTION_PIN = 4;
int RA_SPEED_PIN = 5;
double RA_GEAR_TRAIN = 2;
int RA_DEFAULT_RPM = 800;
int RA_MOTOR_STEPS = 800;
int RA_MOUNT_STEPS = 130;
int RA_MICRO_STEPS = 16;

Stepper raStepper(RA_MOTOR_STEPS, RA_DIRECTION_PIN, RA_SPEED_PIN);
Watch watch;

class Ra
{
private:
  bool parking = false;
  long currentMountPosition = 0;
  long realMountPosition = 0;
  long currentMountPositionStarTime = watch.getRAStarTime(currentMountPosition);
  long raTime = watch.getRAStarTime(currentMountPosition);

  double stepsPerFullTurn = RA_MOUNT_STEPS * RA_MOTOR_STEPS * RA_GEAR_TRAIN * RA_MICRO_STEPS;
  double secondsForFullTurn = 24.00 * 60.00 * 60.00;
  double secondsPerStep = secondsForFullTurn / stepsPerFullTurn;

  long receiveTopSidePosition(long position)
  {
    return position >= 6 * 60 * 60 && position < 18 * 60 * 60
      ? (position + 12 * 60 * 60) % (24 * 60 * 60)
      : position;
  }

  long receiveCurrentMountPosition(long position, long seconds)
  {
    return position + seconds >= 0
      ? (position + seconds) % (24 * 60 * 60)
      : (24 * 60 * 60) + (position + seconds);
  }

  long getSeconds(int hour, int min, int sec)
  {
    return ((((long)hour * 60) + min) * 60) + sec;
  }

  long getStepsToMove(int sec)
  {
    return sec / secondsPerStep;
  }

  long getModulePosition(long position)
  {
    if (position >= 18 * 60 * 60 && position < 24 * 60 * 60)
    {
      return position - 18 * 60 * 60;
    }

    return position + 6 * 60 * 60;
  }

  void move(long steps)
  {
    Serial.println("RA AXIS: move move...");
    // Is the number of steps per command
    int iterationSteps = 10000;
    int index = abs(steps / iterationSteps);
    int remainderSteps = steps % iterationSteps;

    while (index > 0)
    {
      raStepper.step(iterationSteps);
      index--;
    }

    raStepper.step(remainderSteps);
    Serial.println("RA AXIS: move over");
  }

public:
  Ra()
  {
    setRpm(RA_DEFAULT_RPM);
    Serial.println("RA MODULE: initialization finished");
  }

  void init()
  {
    raTime = watch.getRAStarTime(currentMountPosition);

    while (!parking)
    {
      currentMountPositionStarTime = watch.getRAStarTime(currentMountPosition);

      if (raTime != currentMountPositionStarTime)
      {
        Serial.println("RA AXIS: change coordinate");
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
  }

  void setRpm(int rpm)
  {
    raStepper.setSpeed(rpm);
  }

  void setRaTime(int h, int m, int s)
  {
    raTime = getSeconds(h, m, s);
  }

  long getRaTime()
  {
    return raTime;
  }

  void changeParkingState()
  {
    parking = !parking;
  }
};