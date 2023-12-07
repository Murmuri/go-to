#include "../config.h"
#include <Clock.h>
#include <Dec.h>
#include <Ra.h>

const int motorInterfaceType = 1;
const int HOURS_IN_SEC = 60 * 60;
const int INTERATION_STEPS = 10000; // Is the number of steps per command


class MountController
{
  private:
    Dec dec;
    Ra ra(_clock);
    int decCoordinatesDegrees = DEFAULT_DEC_DEGREE;
    int decCoordinatesMinutes = DEFAULT_DEC_MINUTE;
    int decCoordinatesSeconds = DEFAULT_DEC_SECONDS;
    int raCoordinateHours = 0;
    int raCoordinatesMinutes = 0;
    int raCoordinatesSeconds = 0;
    Clock& _clock;

  public:
    MountController(Clock& clock): _clock(clock) {};
    void initialize();
    void update();
    void setRaCoordinateHours(int hour);
    void setRaCoordinateMinutes(int min);
    void setRaCoordinateSeconds(int sec);
    int getRaCoordinateHours();
    int getRaCoordinateMinutes();
    int getRaCoordinateSeconds();
    void setDecCoordinateDegrees(int deg);
    void setDecCoordinateMinutes(int min);
    void setDecCoordinateSeconds(int sec);
    int getDecCoordinateDegrees();
    int getDecCoordinateMinutes();
    int getDecCoordinateSeconds();
};