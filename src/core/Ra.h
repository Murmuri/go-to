#include <Stepper.h>
#include <Config.h>

Stepper raStepper(RA_MOTOR_STEPS, RA_DIRECTION_PIN, RA_SPEED_PIN);

class Ra
{
private:
  int hour = DEFAULT_RA_HOUR;
  int minute = DEFAULT_RA_MINUTE;
  double seconds = DEFAULT_RA_SECONDS;

  int rpm = RA_DEFAULT_RPM;
  double stepsPerFullTurn = (long)RA_MOUNT_STEPS * (long)RA_MOTOR_STEPS * (long)RA_GEAR_TRAIN * (long)RA_MICRO_STEPS;
  double secondsForFullTurn = (double)24 * 60 * 60;
  double secondsPerStep = secondsForFullTurn / stepsPerFullTurn;

public:
  Ra()
  {
    raStepper.setSpeed(rpm);
    Serial.println("Ra module initialized");
  }

  long getSeconds(int h, int m, int s)
  {
    return ((((long)h * 60) + m) * 60) + s;
  }

  void setRpm(int r)
  {
    rpm = r;
    raStepper.setSpeed(rpm);
  }

  void goTo(int h, int m, int s)
  {
    long steps = getStepsToMove(h, m, s);
    Serial.print("Ra steps to move: ");
    Serial.println(steps);

    hour = h;
    minute = m;
    seconds = s;
    // Is the number of steps per command
    int indexSteps = 10000;
    long index = steps / indexSteps;
    int remainder = steps % indexSteps;

    if (steps < 0)
    {
      index = -(index);
    }

    while (index > 0)
    {
      raStepper.step(steps < 0 ? -(indexSteps) : indexSteps);
      index--;
    }
    raStepper.step((int)remainder);
    Serial.println("Ra done");
  }

  double getStepsToMove(int h, int m, int s)
  {
    double toGoSeconds = getSeconds(h, m, s);
    double currentSeconds = getSeconds(hour, minute, seconds);
    double secondsForMove = currentSeconds - toGoSeconds;
    double steps = secondsForMove / secondsPerStep;

    return steps;
  }
};