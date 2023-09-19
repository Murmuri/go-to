#include "Dec.h"

void MotorController::initialize()
{
  setRpm(DEC_DEFAULT_RPM);
  Serial.println("DEC MODULE: initialization finished"); 
}

void MotorController::update()
{
  if (parking)
  {
    return;
  }

  bool changeSide = currentSide != side;

  if (changeSide)
  {
    Serial.println("DEC MODULE: change side");

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
    Serial.println("DEC MODULE: change coordinate");
    long secondsForMove = currentTotalSeconds - totalSeconds;
    long steps = getStepsToMove(secondsForMove);
    move(steps * currentSide);

    currentDegree = degree;
    currentMinute = minute;
    currentSeconds = seconds;
  }
}

void MotorController::setRpm(int rpm)
{
  decStepper.setSpeed(rpm);
}

void MotorController::setCoordinates(int deg, int min, int sec)
{
  degree = deg;
  minute = min;
  seconds = sec;
}

Coordinates MotorController::getCoordinates(Coordinates C)
{
  C.deg = currentDegree;
  C.min = currentMinute;
  C.sec = currentSeconds;

  return (C);
}

void MotorController::setSide(int s)
{
  currentSide = s;
}

void MotorController::setParking(bool p)
{
  parking = p;
}

long MotorController::getDegreesInSeconds(int deg, int min, int sec)
{
  long seconds = ((((long)abs(deg) * 60) + min) * 60) + sec;
  return (deg / abs(deg)) * seconds;
}

long MotorController::getStepsToMove(long secondsForMove)
{
  return secondsForMove / secondsPerStep;
}

void MotorController::move(long steps)
{
  Serial.println("DEC MODULE: move move...");
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
  Serial.println("DEC MODULE: move over");
}
