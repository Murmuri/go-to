#include "../config.h"
#include <Clock.h>
#include <Dec.h>
#include <Ra.h>

const int motorInterfaceType = 1;
const int HOURS_IN_SEC = 60 * 60;
const int INTERATION_STEPS = 10000; // Is the number of steps per command

struct DecCoordinates {
  int deg;
  int min;
  int sec;
};

struct RaCoordinates {
  int hour;
  int min;
  int sec;
};

class MountController
{
  private:
    Dec dec;
    Ra ra(_clock);

    struct DecCoordinates decCoordinates;
    struct RaCoordinates raCoordinates;

    decCoordinates.deg = DEFAULT_DEC_DEGREE;
    decCoordinates.min = DEFAULT_DEC_MINUTE;
    decCoordinates.sec = DEFAULT_DEC_SECONDS;

    raCoordinates.raHorse = 0;
    raCoordinates.raMinute = 0;
    raCoordinates.raSeconds = 0;

    Clock& _clock;


  public:
    MountController(Clock& clock): _clock(clock) {}

    void initialize()

    void update()

    void setRaCoordinate(int h, int m, int s)

    void getRaCoordinate(int &h, int &m, int &s)

    void setDecCoordinate(int d, int m, int s)

    void getDecCoordinate(int &d, int &m, int &s)
};