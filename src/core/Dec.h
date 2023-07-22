#include <Stepper.h>
#include <Config.h>

Stepper decStepper(DEC_MOTOR_STEPS, DEC_DIRECTION_PIN, DEC_SPEED_PIN);

class Dec
{
private:
  int degree = DEFAULT_DEC_DEGREE;
  int minute = DEFAULT_DEC_MINUTE;
  int seconds = DEFAULT_DEC_SECONDS;

  int rpm = DEC_DEFAULT_RPM;
  double stepsPerFullTurn = (long)DEC_MOUNT_STEPS * (long)DEC_MOTOR_STEPS * (long)DEC_GEAR_TRAIN * (long)DEC_MICRO_STEPS;
  double secondsForFullTurn = (double)360 * 60 * 60;
  double secondsPerStep = (double)(secondsForFullTurn / stepsPerFullTurn);

public:
  Dec()
  {
    decStepper.setSpeed(rpm);
    Serial.println("Dec module initialized");
  }

  long degreeSeconds(int d, int m, int s)
  {
    return ((((long)d * 60) + m) * 60) + s;
  }

  void setRpm(int r)
  {
    rpm = r;
    decStepper.setSpeed(rpm);
  }

  void goTo(int d, int m, int s)
  {
    long steps = getStepsToMove(d, m, s);
    Serial.print("Ra steps to move: ");
    Serial.println(steps);

    degree = d;
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
      decStepper.step(steps < 0 ? -(indexSteps) : indexSteps);
      index--;
    }

    decStepper.step((int)remainder);
    Serial.println("Dec done");
  }

  double getStepsToMove(int d, int m, int s)
  {
    double toGoSeconds = degreeSeconds(d, m, s);
    double currentSeconds = degreeSeconds(degree, minute, seconds);
    double secondsForMove = currentSeconds - toGoSeconds;
    double steps = secondsForMove / secondsPerStep;

    return steps;
  }
};