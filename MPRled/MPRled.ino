// Capacitive touch

#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

Adafruit_MPR121 cap = Adafruit_MPR121();
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

//
////leds
//#include <FastLED.h>
//
//#define LED_PIN     14
//#define NUM_LEDS    15
//#define BRIGHTNESS  64
//#define LED_TYPE    WS2812B
//#define COLOR_ORDER GRB
//CRGB leds[NUM_LEDS];
//       
//#define UPDATES_PER_SECOND 100
//CRGBPalette16 currentPalette;
//TBlendType    currentBlending;


//io

 #include "secrets.h"

AdafruitIO_Feed *messages = io.feed("messages");


void setup() {
  Serial.begin(9600);
// cap
  while (!Serial) { // needed to keep leonardo/micro from starting too fast!
    delay(10);
     Serial.print("connecting to adafruit IO");
 
  io.connect();
  messages->onMessage(handleMessage);
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

 
  Serial.println();
  Serial.println(io.statusText());
    
    
  }
  
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
//
// //led
//    delay( 3000 ); // power-up safety delay
//    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
//    FastLED.setBrightness(  BRIGHTNESS );
//    pinMode(14, OUTPUT);

//io stuff
 //  while(! Serial);
   Serial.print("connecting to adafruit IO");
 
  io.connect();
  messages->onMessage(handleMessage);
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

 
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {
  io.run();
  
  // Get the currently touched pads
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
      //messages->save("yes" + i);
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
    }
  }
 
  // reset our state
  lasttouched = currtouched;


//  
//    //led
//    static uint8_t startIndex = 0;
//    startIndex = startIndex +1; //motion speed
//
//   FastLED.setBrightness(  BRIGHTNESS );
//    FillLEDsFromPaletteColors( startIndex);
//    FastLED.show();
//    FastLED.delay(1000 / UPDATES_PER_SECOND);
}



//led
//void FillLEDsFromPaletteColors( uint8_t colorIndex)
//{
//  
//    uint8_t brightness = 255;
//    
//    for( int i = 0; i < NUM_LEDS; i++) {
//        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
//        colorIndex += 3;
//    }
//}
//
//

//io
void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <- ");
  Serial.println(data->value());

}
