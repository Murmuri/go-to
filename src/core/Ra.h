#include <Stepper.h>
#include <MountController.h>

const int POSITIVE_SIDE = 1;
const int NEGATIVE_SIDE = -1;

Stepper raStepper(RA_MOTOR_STEPS, RA_DIRECTION_PIN, RA_SPEED_PIN);

class Ra
{
  private:
    bool parking = false;
    long currentMountPosition = 0;
    long realMountPosition = 0;
    long currentMountPositionStarTime = 0;
    long raTime = 0;

    double stepsPerFullTurn = RA_MOUNT_STEPS * RA_MOTOR_STEPS * RA_GEAR_TRAIN * RA_MICRO_STEPS;
    double secondsForFullTurn = 24.00 * HOURS_IN_SEC;
    double secondsPerStep = secondsForFullTurn / stepsPerFullTurn;

    long receiveTopSidePosition(long position)

    long receiveCurrentMountPosition(long position, long seconds)

    long getHoursInSeconds(int hour, int min, int sec)

    long getStepsToMove(int sec)

    long getModulePosition(long position)

    void move(long steps)

    Clock& _clock;


  public:
    Ra(Clock& clock): _clock(clock) {}
    
    void initialize()

    void update()

    void setRpm(int rpm)

    void setCoordinates(int h, int m, int s)
  
    int getSide()

    void setParking(bool parking)
};