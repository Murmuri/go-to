#include <Arduino.h>
#include "./config.h"
#include "./core/Control.h"
#include "./core/MountController.h"
#include "./core/Clock.h"

Clock clock;
MountController mount(clock);
Control control(mount, clock);

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