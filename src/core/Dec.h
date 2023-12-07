#include <Stepper.h>
#include <Math.h>
#include <MountController.h>

Stepper decStepper(DEC_MOTOR_STEPS, DEC_DIRECTION_PIN, DEC_SPEED_PIN);


class Dec
{
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
    double secondsForFullTurn = 360.00 * HOURS_IN_SEC;
    double secondsPerStep = secondsForFullTurn / stepsPerFullTurn;

    long getDegreesInSeconds(int deg, int min, int sec);
    long getStepsToMove(long secondsForMove);
    void move(long steps);


  public:
    void initialize()
    void update()
    void setRpm(int rpm)
    void setCoordinates(int deg, int min, int sec)
    void setSide(int newSide)
    void setParking(bool parking)
};