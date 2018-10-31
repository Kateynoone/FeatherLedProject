#include <CapacitiveSensor.h>
#include "secrets.h"
#include <ESP8266WiFi.h>
//int count = 0;
#define IO_LOOP_DELAY 5000
//unsigned long lastUpdate = 0;
// set up the 'counter' feed

AdafruitIO_Feed *analog = io.feed("analog");

CapacitiveSensor cs_16_2 = CapacitiveSensor(16, 2);

long sensor_reading;

void setup() {
  Serial.begin(115200);
  while(! Serial);
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}

void loop() {
  io.run();
 sensor_reading =  cs_16_2.capacitiveSensor(30);

 Serial.print("sending -> ");
 Serial.println(sensor_reading);
 analog->save(sensor_reading);
 delay(500);
 
  
}

