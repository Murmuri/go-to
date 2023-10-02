#include <Wire.h> 
#include <LiquidCrystal.h>
#include "../config.h"

#define DSP_ROWS            2
#define DSP_COLS            16
#define DSP_REFRESH_MS      250
#define DPS_BLINKING_MS     300


class Display 
{
  public:
    Display() : _lcd(
      LiquidCrystal(
        DSP_REGISTER_SEL_PIN, 
        DSP_ENABLE_PIN, 
        DSP_DATA_PIN7, 
        DSP_DATA_PIN6, 
        DSP_DATA_PIN5, 
        DSP_DATA_PIN4
      )
    ) {}
    
    void initialize(int brightness);

    void renderGotoItem();
   
    void renderManualItem();

    void renderCoordinateItem();

    void renderTimeItem();

    void renderBrightItem();

    void renderObjectsItem();
   

  private:
    LiquidCrystal _lcd;
};