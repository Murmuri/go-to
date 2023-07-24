#include <Stepper.h>
#include <Config.h>
#include <Math.h>

Stepper decStepper(DEC_MOTOR_STEPS, DEC_DIRECTION_PIN, DEC_SPEED_PIN);

class Dec
{
private:
  int degree = DEFAULT_DEC_DEGREE;
  int minute = DEFAULT_DEC_MINUTE;
  int seconds = DEFAULT_DEC_SECONDS;
  long currentStep = 0;
  double stepsPerFullTurn = DEC_MOUNT_STEPS * DEC_MOTOR_STEPS * DEC_GEAR_TRAIN * DEC_MICRO_STEPS;
  double secondsForFullTurn = 360.00 * 60.00 * 60.00;
  double secondsPerStep = secondsForFullTurn / stepsPerFullTurn;

public:
  Dec()
  {
    setRpm(DEC_DEFAULT_RPM);
    Serial.println("DEC module initialized");
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

  void goTo(int deg, int min, int sec)
  {
    long steps = getStepsToMove(deg, min, sec);
   
    move(steps);

    degree = deg;
    minute = min;
    seconds = sec;
    currentStep += steps;
    Serial.println("DEC done");
  }

  double getStepsToMove(int deg, int min, int sec)
  {
    double degreeSeconds = getDegreeSeconds(deg, min, sec);
    double currentSeconds = getDegreeSeconds(degree, minute, seconds);
    double secondsForMove = currentSeconds - degreeSeconds;
    double steps = secondsForMove / secondsPerStep;

    return steps;
  }

  void move(long steps) 
  {
    Serial.print("DEC move...");
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
  }
};