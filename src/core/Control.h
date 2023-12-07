#include "../config.h"
#include "Keypad.h"

class Control 
{
  public:
    enum State { GOTO_MENU, COORDINATE_MENU, TIME_MENU};
    Control(MountController& mount, Clock& clock): _mount(mount), _clock(clock) {}
    void initialize();
    void update();

  private:
    State _state;
    Keypad _keypad;
    Clock& _clock;
    MountController& _mount;

    void goToMenu();
    void coordinateMenu();
    void timeMenu();

    inline void changeState(State new_state) 
    {
      _state = new_state;
    }
};