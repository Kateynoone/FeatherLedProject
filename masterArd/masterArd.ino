#include <Wire.h>
union                                               // Union used to convert raw data to 'float'.
{
    float dRXVal;
    byte bRawData[4];
}floatData;

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
}

byte x = 0;

void loop() {
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting

  x++;
  delay(500);
   if (Wire.available() >= 4)                      // Make sure there are four bytes.
    {
        for (int i = 0; i < 4; i++)                 // Receive the raw 'float' data.
            floatData.bRawData[i] = Wire.read();    //    "     "     "     "     "
        Serial.println(floatData.dRXVal,3);         // Print the result.
    }
}


