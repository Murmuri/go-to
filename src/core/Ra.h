#include "../config.h"
#include <Stepper.h>
#include <Watch.h>

Stepper raStepper(RA_MOTOR_STEPS, RA_DIRECTION_PIN, RA_SPEED_PIN);
Watch watch;

struct Coordinates {
  int hour;
  int min;
  int sec;
};


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

    long receiveCurrentMountPosition(long position, long seconds)

    long getHoursInSeconds(int hour, int min, int sec)

    long getStepsToMove(int sec)

    long getModulePosition(long position)

    void move(long steps)


  public:
    void initialize()

    void update()

    void setRpm(int rpm)

    void setCoordinates(int h, int m, int s)

    Coordinates getCoordinates(Coordinates C)
  
    int getSide()

    void setParking(bool parking)
};