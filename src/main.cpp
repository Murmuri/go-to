#include <Arduino.h>
#include <Config.h>
#include <Arduino_Threads.h>
#include <Control.h>

Thread controlThread = Thread();
Control control;

void setup()
{
  Serial.begin(SERIAL_SPEED);
  Serial.print("MAIN MODULE: speed ");
  Serial.println(SERIAL_SPEED);

  pinMode(DEC_DIRECTION_PIN, OUTPUT);
  pinMode(DEC_SPEED_PIN, OUTPUT);
  pinMode(RA_DIRECTION_PIN, OUTPUT);
  pinMode(RA_SPEED_PIN, OUTPUT);
  pinMode(WATCH_CLK_PIN, OUTPUT);
  pinMode(WATCH_DAT_PIN, OUTPUT);
  pinMode(WATCH_RST_PIN, OUTPUT);

  controlThread.onRun(control.init());
  controlThread.run();

  Serial.print("MAIN MODULE: Initialization completed");
}

void loop() {}