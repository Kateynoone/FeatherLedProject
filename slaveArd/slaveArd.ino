
#include <Wire.h>

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);   
long sensor_reading;

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);           // start serial for output
}

void loop() {
  delay(100);
//  sensor_reading =  cs_4_2.capacitiveSensor(30);
//  Serial.println(sensor_reading);
//  Wire.beginTransmission();
//  Wire.send(sensor_reading);
//  Wire.endTransmission();
  
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
//  while (1 < Wire.available()) { // loop through all but the last
//    char c = Wire.read(); // receive byte as a character
//    Serial.print(c);         // print the character
//  }
//  int x = Wire.read();    // receive byte as an integer
//  Serial.println(x);         // print the integer

}
