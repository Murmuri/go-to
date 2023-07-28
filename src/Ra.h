#include <Stepper.h>
#include <Config.h>
#include <Watch.h>

Stepper raStepper(RA_MOTOR_STEPS, RA_DIRECTION_PIN, RA_SPEED_PIN);
Watch watch;

class Ra
{
private:
  long mountTime = 0;
  long mountStarTime = 0;
  double stepsPerFullTurn = RA_MOUNT_STEPS * RA_MOTOR_STEPS * RA_GEAR_TRAIN * RA_MICRO_STEPS;
  double secondsForFullTurn = 24.00 * 60.00 * 60.00;
  double secondsPerStep = secondsForFullTurn / stepsPerFullTurn;

public:
  Ra()
  {
    setRpm(RA_DEFAULT_RPM);
    Serial.println("RA MODULE: initialization finished");
  }

  void init()
  {
    mountStarTime = watch.getRAStarTime(mountTime);

    while (true)
    {
      long starTime = watch.getRAStarTime(mountTime);
      
      if (starTime != mountStarTime)
      {
        Serial.println("RA AXIS: change coordinate");
        long secondsForMove = starTime - mountStarTime;
        long steps = getStepsToMove(secondsForMove);

        move(steps);
        // TODO
        if (mountTime + secondsForMove >= 24 * 60 * 60)
        {
          mountTime = secondsForMove - 24 * 60 * 60;
        }
        else if (mountTime + secondsForMove < 0)
        {
          mountTime = 24 * 60 * 60 + secondsForMove;
        }
        else
        {
          mountTime += secondsForMove;
        }
      }
    }
  }

  long getSeconds(int hour, int min, int sec)
  {
    return ((((long)hour * 60) + min) * 60) + sec;
  }

  void setRpm(int rpm)
  {
    raStepper.setSpeed(rpm);
  }

  long getStepsToMove(int sec)
  {
    return sec / secondsPerStep;
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

  void setMountStarTime(int h, int m, int s)
  {
    mountStarTime = getSeconds(h, m, s);
  }

  long getMountStarTime()
  {
    return mountStarTime;
  }
};