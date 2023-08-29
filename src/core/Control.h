#include <Arduino.h>
#include "../config.h"
#include "./MountController.h"
#include "./Clock.h"

class Control
{
public:
  enum State
  {
    MAIN,
    GOTO,
    CALIB,
    CATALOG,
    TIME,
    POSITION,
    BRIGHT
  };
  Control(
    MountController& mount, 
    Clock& clock
  ) {}
  void initialize();
  void update();

private:
  void mainMenu();
  void positionMenu();
  void brightnessMenu();
  void gotoMenu();
  void timeMenu();
  void calibrationMenu();
  void catalogueMenu();
  void manualControl();
  
  Clock& _clock;
  MountController& _mount;
};