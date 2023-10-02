#include <IRremote.h>

#define KP_KEY_A             0xFF6897
#define KP_KEY_B             0xFFB04F
#define KP_KEY_1             0xFFA25D
#define KP_KEY_2             0xFF629D
#define KP_KEY_3             0xFFE21D
#define KP_KEY_4             0xFF22DD
#define KP_KEY_5             0xFF02FD 
#define KP_KEY_6             0xFFC23D
#define KP_KEY_7             0xFFE01F 
#define KP_KEY_8             0xFFA857
#define KP_KEY_9             0xFF906F
#define KP_KEY_0             0xFF9867
#define KP_KEY_UP_ARROW      0xFF18E7 
#define KP_KEY_DOWN_ARROW    0xFF4AB5 
#define KP_KEY_RIGHT_ARROW   0xFF5AA5
#define KP_KEY_LEFT_ARROW    0xFF10EF
#define KP_KEY_OK            0xFF38C7

#define KP_UPDATE_MS         200     

class Keypad 
{
  public:
    Keypad() : _recv(IRrecv(KEYPAD_IR_PIN)) {}

    void initialize() 
    {
      _recv.enableIRIn();
      _recv.blink13(false);
    }
    // returns true if the given key was pressed for longer than SHORT_HOLD_TIME_MS
    inline boolean pushed(uint32_t key_code) 
    { 
      return pressed_internal(key_code, SHORT_HOLD_TIME_MS); 
    }
    // returns true if the given key was pressed for longer than LONG_HOLD_TIME_MS
    inline boolean pressed(uint32_t key_code) 
    { 
      return pressed_internal(key_code, LONG_HOLD_TIME_MS); 
    }

    void update() 
    {
      _hold_time = 0;

      if (_last_used_key == 0 && (millis() - _last_update) < KP_UPDATE_MS) return;
      _last_update = millis();

      uint32_t new_key = get_key();
    
      if (new_key == _used_key) return;

      _last_used_key = _used_key;
      _used_key = new_key;
      _hold_time = millis() - _press_time;
      _press_time = millis();
    }

  private:
    uint32_t get_key() 
    {
      decode_results results;
      if (!_recv.decode(&results)) return 0;

      _recv.resume();

      return (results.value == 0xFFFFFFFF ? _used_key : results.value) ;
    }

    IRrecv _recv;

    uint32_t _used_key = 0;         // currently pressed key
    uint32_t _last_used_key = 0;    // key pressed before previous key change

    unsigned long _hold_time = 0;   // millis since last key change
    unsigned long _press_time = 0;  // millis of last key change

    unsigned long _last_update = 0; // millis since last key check
};