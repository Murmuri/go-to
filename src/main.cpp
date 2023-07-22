#include <Arduino.h>
#include <Config.h>
#include <core/Dec.h>
#include <core/Ra.h>

const int motorInterfaceType = 1;
Dec declination;
Ra ra;

void setup()
{
  Serial.begin(SERIAL_SPEED);
  Serial.print("Initialization completed");
}

void loop() 
{
  while (Serial.available() == 0) {}
  
  int dd = Serial.parseInt(); 
  int dm = Serial.parseInt(); 
  int ds = Serial.parseInt();
  int rh = Serial.parseInt(); 
  int rm = Serial.parseInt(); 
  int rs = Serial.parseInt(); 
  int code = Serial.parseInt(); 

  Serial.print("Code: ");
  Serial.println(code);

  if (code == 99)
  {
    Serial.println("Go");
    declination.goTo(dd, dm, ds);
    ra.goTo(rh, rm, rs);
    Serial.println("Done");
  }
}