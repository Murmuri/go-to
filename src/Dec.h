#include <Stepper.h>
#include <Math.h>

int DEC_DIRECTION_PIN = 2;
int DEC_SPEED_PIN = 3;
double DEC_GEAR_TRAIN = 3.375;
int DEC_DEFAULT_RPM = 800;
int DEC_MOTOR_STEPS = 800;
int DEC_MOUNT_STEPS = 65;
int DEC_MICRO_STEPS = 16;
int DEFAULT_DEC_DEGREE = 90;
int DEFAULT_DEC_MINUTE = 0;
int DEFAULT_DEC_SECONDS = 0;

Stepper decStepper(DEC_MOTOR_STEPS, DEC_DIRECTION_PIN, DEC_SPEED_PIN);

class Dec
{
private:
  bool parking = false;
  int currentDegree = DEFAULT_DEC_DEGREE;
  int currentMinute = DEFAULT_DEC_MINUTE;
  int currentSeconds = DEFAULT_DEC_SECONDS;
  int currentSide = 1; // "1" - right side, "-1" - left side 
  int side = 1;
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
    while (!parking)
    {
      bool changeSide = currentSide != side;
      
      if (changeSide) 
      {
        Serial.println("DEC AXIS: change side");
        long stepsToDefaultPosition = getStepsToMove(
          getDegreeSeconds(currentDegree, currentMinute, currentSeconds) 
          - getDegreeSeconds(DEFAULT_DEC_DEGREE, DEFAULT_DEC_MINUTE, DEFAULT_DEC_SECONDS)
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

  int changeSide()
  {
    currentSide = currentSide * -1;
  }

  int changeParkingState()
  {
    parking = !parking;
  }
};