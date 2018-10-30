//ledStuff

#include <FastLED.h>
#define LED_PIN     14
#define NUM_LEDS    15
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette; 
TBlendType    currentBlending;


//io stuff

#include "secrets.h"
AdafruitIO_Feed *color = io.feed("colorchange");



void setup() {
 // io connection stuff!
 
  Serial.begin(115200);
 while(! Serial);
 Serial.print("connecting to adafruit IO");
 
 io.connect();
 
  color->onMessage(handleMessage); //handles it when a message is received from io
while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText());
  color->get();

//led setup
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p; // palette the led's automatically start on
    currentBlending = LINEARBLEND;
FastLED.show();
}


  
void loop() {
 io.run();

  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
 

}
void handleMessage(AdafruitIO_Data *data) {

  // print RGB values and hex value
  Serial.println("Received HEX: ");
  Serial.println(data->value());



  for(int i=0; i<NUM_LEDS; ++i) {
    leds[i] = 0xFF44DD;
  }

 
}


