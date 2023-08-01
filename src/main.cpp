#include <Arduino.h>
#include <Thread.h>
#include <Control.h>

int SERIAL_SPEED = 9600;

Thread controlThread = Thread();
Control control;

void initControlThread()
{
  control.init();
}

void setup()
{
  Serial.begin(SERIAL_SPEED);
  Serial.print("MAIN MODULE: speed");
  Serial.println(SERIAL_SPEED);

  pinMode(WATCH_CLK_PIN, OUTPUT);
  pinMode(WATCH_DAT_PIN, OUTPUT);
  pinMode(WATCH_RST_PIN, OUTPUT);

  controlThread.enabled = true;
  controlThread.onRun(initControlThread);
  controlThread.run();

  Serial.print("MAIN MODULE: Initialization completed");
}

void loop() {}
