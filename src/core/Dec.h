#include <Stepper.h>
#include <Config.h>
#include <Math.h>

Stepper decStepper(DEC_MOTOR_STEPS, DEC_DIRECTION_PIN, DEC_SPEED_PIN);

class Dec
{
private:
  int currentDegree = DEFAULT_DEC_DEGREE;
  int currentMinute = DEFAULT_DEC_MINUTE;
  int currentSeconds = DEFAULT_DEC_SECONDS;
  int degree = DEFAULT_DEC_DEGREE;
  int minute = DEFAULT_DEC_MINUTE;
  int seconds = DEFAULT_DEC_SECONDS;
  double stepsPerFullTurn = DEC_MOUNT_STEPS * DEC_MOTOR_STEPS * DEC_GEAR_TRAIN * DEC_MICRO_STEPS;
  double secondsForFullTurn = 360.00 * 60.00 * 60.00;
  double secondsPerStep = secondsForFullTurn / stepsPerFullTurn;

public:
  Dec()
  {
    setRpm(DEC_DEFAULT_RPM);
    Serial.println("DEC MODULE: initialization finished");
  }

  long getDegreeSeconds(int deg, int min, int sec)
  {
    long seconds = ((((long)abs(deg) * 60) + min) * 60) + sec;
    return (deg / abs(deg)) * seconds;
  }

  void setRpm(int rpm)
  {
    decStepper.setSpeed(rpm);
  }

  void init()
  {
    while (true)
    {
      long currentTotalSeconds = getDegreeSeconds(currentDegree, currentMinute, currentSeconds);
      long totalSeconds = getDegreeSeconds(degree, minute, seconds);

      if (currentTotalSeconds != totalSeconds)
      {
        Serial.println("DEC AXIS: change coordinate");
        long secondsForMove = currentTotalSeconds - totalSeconds;
        long steps = getStepsToMove(secondsForMove);
        move(steps);
        currentDegree = degree;
        currentMinute = minute;
        currentSeconds = seconds;
      }
    }
  }

  long getStepsToMove(long secondsForMove)
  {
    return secondsForMove / secondsPerStep;
  }

  void move(long steps)
  {
    Serial.println("DEC AXIS: move move...");
    // Is the number of steps per command
    int iterationSteps = 10000;
    int index = abs(steps / iterationSteps);
    int remainderSteps = steps % iterationSteps;

    while (index > 0)
    {
      decStepper.step(iterationSteps);
      index--;
    }

    decStepper.step(remainderSteps);
    Serial.println("DEC AXIS: move over");
  }

  long setDegree(int deg)
  {
    degree = deg;
  }

  long setMinute(int min)
  {
    minute = min;
  }

  long setSeconds(int sec)
  {
    seconds = sec;
  }

  int getDegree()
  {
    return currentDegree;
  }

  int getMinute()
  {
    return currentMinute;
  }

  int getSeconds()
  {
    return currentSeconds;
  }
};