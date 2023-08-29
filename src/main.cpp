#include <Arduino.h>
#include "./config.h"
#include "./core/Control.h"
#include "./core/MountController.h"
#include "./core/Clock.h"

Clock clock;
MountController mount;

Control control(mount, watch);

void setup()
{
  Serial.begin(SERIAL_SPEED);
  delay(10);
  control.initialize();
  delay(100);
}

void loop()
{
  control.update();
  delay(10);
}