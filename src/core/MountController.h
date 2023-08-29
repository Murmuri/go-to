#include "../config.h"

#include <Dec.h>
#include <Ra.h>

const int motorInterfaceType = 1;

Dec dec;
Ra ra;

class MountController
{
public:
  void initialize()
  {
    dec.initialize();
    ra.initialize();
    long raTime = ra.getRaTime();
    raHorse = raTime/(60*60);
    raMinute = (raTime / 60) % 60;
    raSeconds = raTime % 60;

    Serial.println("MOUNT CONTROLLER MODULE: initialization finished");
  }

  void update()
  {
    ra.setRaTime(raHorse, raMinute, raSeconds);
    dec.setSide(ra.getSide());
    dec.setDegree(decDegree, decMinute, decSeconds);

    dec.update();
    ra.update();
  }

  void setRaCoordinate(int h, int m, int s)
  {
    raHorse = h;
    raMinute = m;
    raSeconds = s;
  }

  void setDecCoordinate(int d, int m, int s)
  {
    decDegree = d;
    decMinute = m;
    decSeconds = s;
  }

private:
  int decDegree = DEFAULT_DEC_DEGREE;
  int decMinute = DEFAULT_DEC_MINUTE;
  int decSeconds = DEFAULT_DEC_SECONDS;
  int raHorse = 0;
  int raMinute = 0;
  int raSeconds = 0;
};