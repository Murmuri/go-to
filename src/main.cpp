#include <Arduino.h>
#include <Config.h>
#include <GyverOS.h>
#include <Control.h>

GyverOS<TUSK_COUNT> OS;
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
  OS.attach(0, control.init());
  OS.start(0); 

  Serial.print("MAIN MODULE: Initialization completed");
}

void loop() {}