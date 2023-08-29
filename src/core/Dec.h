#include <Stepper.h>
#include <Math.h>
#include "../config.h"

Stepper decStepper(DEC_MOTOR_STEPS, DEC_DIRECTION_PIN, DEC_SPEED_PIN);

class Dec
{
public:
  void initialize()
  {
    setRpm(DEC_DEFAULT_RPM);
    Serial.println("DEC MODULE: initialization finished"); 
  }

  void update()
  {
    if (parking)
    {
      return;
    }

    bool changeSide = currentSide != side;

    if (changeSide)
    {
      Serial.println("DEC AXIS: change side");

      long stepsToDefaultPosition = getStepsToMove(
        getDegreeSeconds(currentDegree, currentMinute, currentSeconds) - getDegreeSeconds(DEFAULT_DEC_DEGREE, DEFAULT_DEC_MINUTE, DEFAULT_DEC_SECONDS)
      );
      move(stepsToDefaultPosition * currentSide);

      currentSide = side;
      currentDegree = DEFAULT_DEC_DEGREE;
      currentMinute = DEFAULT_DEC_MINUTE;
      currentSeconds = DEFAULT_DEC_SECONDS;
    }

    long currentTotalSeconds = getDegreeSeconds(currentDegree, currentMinute, currentSeconds);
    long totalSeconds = getDegreeSeconds(degree, minute, seconds);

    if (currentTotalSeconds != totalSeconds)
    {
      Serial.println("DEC AXIS: change coordinate");
      long secondsForMove = currentTotalSeconds - totalSeconds;
      long steps = getStepsToMove(secondsForMove);
      move(steps * currentSide);

      currentDegree = degree;
      currentMinute = minute;
      currentSeconds = seconds;
    }
  }

  void setRpm(int rpm)
  {
    decStepper.setSpeed(rpm);
  }

  long setDegree(int deg, int min, int sec)
  {
    degree = deg;
    minute = min;
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

  void setSide(int newSide)
  {
    currentSide = newSide;
  }

  void changeParkingState()
  {
    parking = !parking;
  }

private:
  bool parking = false;
  int currentDegree = DEFAULT_DEC_DEGREE;
  int currentMinute = DEFAULT_DEC_MINUTE;
  int currentSeconds = DEFAULT_DEC_SECONDS;
  // "1" - right side, "-1" - left side
  int currentSide = 1;
  int side = 1;
  int degree = DEFAULT_DEC_DEGREE;
  int minute = DEFAULT_DEC_MINUTE;
  int seconds = DEFAULT_DEC_SECONDS;
  double stepsPerFullTurn = DEC_MOUNT_STEPS * DEC_MOTOR_STEPS * DEC_GEAR_TRAIN * DEC_MICRO_STEPS;
  double secondsForFullTurn = 360.00 * 60.00 * 60.00;
  double secondsPerStep = secondsForFullTurn / stepsPerFullTurn;

  long getDegreeSeconds(int deg, int min, int sec)
  {
    long seconds = ((((long)abs(deg) * 60) + min) * 60) + sec;
    return (deg / abs(deg)) * seconds;
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
};