#include "Display.h"
#include "Control.h"

void Display::initialize(int brightness)
{
  _lcd.begin(DSP_COLS, DSP_ROWS);
  _lcd.createChar(0, arc_minute);
  _lcd.createChar(1, arc_second);
  _lcd.createChar(2, arr_up);
  _lcd.createChar(3, arr_down);
  _lcd.createChar(4, cross);
  _lcd.createChar(5, shadow_two);
  _lcd.noCursor();
  _lcd.clear();

  pinMode(DSP_ANODE_PIN, OUTPUT);
  set_brightness(brightness);

  delay(100);

  _lcd.setCursor(0, 0);
  _lcd.print(F("Sins technology's"));

  _lcd.setCursor(0, 1);
  _lcd.print(F("Arduino star tracker: "));
  _lcd.print(VERSION);

  delay(2000);
}

void Display::renderGotoItem()
{
  _lcd.setCursor(0, 0);
  _lcd.print(F("> GO TO"));
  _lcd.setCursor(0, 1);
  _lcd.print(F("  MANUAL CONTROL"));
}

void Display::renderManualItem()
{
  _lcd.setCursor(0, 0);
  _lcd.print(F("> MANUAL CONTROL"));
  _lcd.setCursor(0, 1);
  _lcd.print(F("  GET COORDINATE"));
}

void Display::renderCoordinateItem()
{
  _lcd.setCursor(0, 0);
  _lcd.print(F("> GET COORDINATE"));
  _lcd.setCursor(0, 1);
  _lcd.print(F("  TIME"));
}

void Display::renderTimeItem()
{
  _lcd.setCursor(0, 0);
  _lcd.print(F("> TIME"));
  _lcd.setCursor(0, 1);
  _lcd.print(F("  BRIGHT SETTINGS"));
}

void Display::renderBrightItem()
{
  _lcd.setCursor(0, 0); _lcd.print(F("> BRIGHT SETTINGS");
  _lcd.setCursor(0, 1); _lcd.print(F("  OBJECTS");
}

void Display::renderObjectsItem()
{
  _lcd.setCursor(0, 0); _lcd.print(F("  BRIGHT SETTINGS");
  _lcd.setCursor(0, 1); _lcd.print(F("> OBJECTS");
}
