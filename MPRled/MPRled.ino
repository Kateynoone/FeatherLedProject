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
//leds
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


extern CRGBPalette16 myPurplePalette;
extern const TProgmemPalette16 myPurplePalette_p PROGMEM;


//io

 #include "secrets.h"

AdafruitIO_Feed *messages = io.feed("messages");


void setup() {
  Serial.begin(9600);
// cap
//  while (!Serial){ // needed to keep leonardo/micro from starting too fast!
//    delay(10);}
  
  Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");

 //led
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
   // pinMode(14, OUTPUT);
   
    currentPalette = RainbowColors_p; // palette the led's automatically start on
    currentBlending = LINEARBLEND;

//io stuff
   while(! Serial);
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
   //led
    static uint8_t startIndex = 0;
    startIndex = startIndex +1; //motion speed

   FastLED.setBrightness(  BRIGHTNESS );
    FillLEDsFromPaletteColors( startIndex);
    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);
    
  // Get the currently touched pads
  currtouched = cap.touched();
 
  for (uint8_t i=0; i<12; i++) {

    
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      messages->save(i);
      if (i == 1){currentPalette = RainbowColors_p; currentBlending= LINEARBLEND;
     } else if (i==3){currentPalette = LavaColors_p; currentBlending= LINEARBLEND;
     } else if (i==5){ currentPalette = PartyColors_p; currentBlending= NOBLEND;
     } else if (i==7){ currentPalette = ForestColors_p; currentBlending= NOBLEND; 
     } else if (i==9){ currentPalette = CloudColors_p; currentBlending= NOBLEND;
     } else if (i==11){ currentPalette = myPurplePalette_p; currentBlending= LINEARBLEND;}
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
     // Serial.print(i); Serial.println(" released");
     currentPalette = OceanColors_p;
//     x= i
    }
  }
 //Serial.println();
// while(x == 1){
//  currentPalette = LavaColors_p;  currentBlending = LINEARBLEND;
// } //else { currentPalette = RainbowColors_p;  currentBlending = LINEARBLEND; }
//  // reset our state
 lasttouched = currtouched;
 }


//led
void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

//io
void handleMessage(AdafruitIO_Data *data) {

  Serial.print("received <- ");
  Serial.println(data->value());

}

const TProgmemPalette16 myPurplePalette_p PROGMEM =
{
    CRGB::Purple,
    CRGB::Gray, // 'white' is too bright compared to red and blue
    CRGB::Purple,
    CRGB::Pink,
    
    CRGB::Purple,
    CRGB::Gray,
    CRGB::Purple,
    CRGB::Pink,
    
    CRGB::Purple,
    CRGB::Gray,
    CRGB::Gray,
    CRGB::Black,
    CRGB::Black
};

