#include "../config.h"
#include "Keypad.h"

#define C_ARROW_UP 				      KP_KEY_UP_ARROW
#define C_ARROW_LEFT            KP_KEY_LEFT_ARROW
#define C_ARROW_RIGHT           KP_KEY_RIGHT_ARROW
#define C_ARROW_DOWN            KP_KEY_DOWN_ARROW     
#define C_ENTER					        KP_KEY_OK
#define C_EXIT					        KP_KEY_A
#define C_B					            KP_KEY_B
#define C_N1					          KP_KEY_1
#define C_N2					          KP_KEY_2
#define C_N3					          KP_KEY_3        
#define C_N4					          KP_KEY_4
#define C_N5					          KP_KEY_5
#define C_N6					          KP_KEY_6
#define C_N7					          KP_KEY_7
#define C_N8					          KP_KEY_8
#define C_N9					          KP_KEY_9
#define C_N0					          KP_KEY_0

class Control 
{
  public:
    enum State { GOTO, MANUAL, COORDINATE, TIME, BRIGHT, OBJECTS };

    Control(MountController& mount, Clock& clock): _mount(mount), _clock(clock) {}

    void initialize();

    void update();

  private:
    void gotoItem();

    void manualControlItem();

    void coordinateItem();

    void timeItem();

    void brightItem();

    void objectsItem();

    void gotoMenu();

    void manualControlMenu();

    void coordinateMenu();

    void timeMenu();

    void brightMenu();

    void objectsMenu();

    inline void changeState(State new_state) 
    {
      _state = new_state;
    }

    inline void changeSubState(State new_state) 
    {
      _subState = new_state;
    }

    State _state;
    Keypad _keypad;
    State _subState;

    Clock& _clock;
    MountController& _mount;
};

#endif
