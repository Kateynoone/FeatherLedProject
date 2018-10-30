#include <FastLED.h>
 // led stuff
#define LED_PIN     14
#define NUM_LEDS    15
#define BRIGHTNESS  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette; 
TBlendType    currentBlending;

// io stuff
 #include "secrets.h"

AdafruitIO_Feed *color = io.feed("colorchange");

void setup() {
    
   Serial.begin(115200);
//io stuff
 while(! Serial);
 Serial.print("connecting to adafruit IO");
 
 io.connect();

  // set up a message handler for the count feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  color->onMessage(handleMessage);

  // wait for an MQTT connection
  // NOTE: when blending the HTTP and MQTT API, always use the mqttStatus
  // method to check on MQTT connection status specifically
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
 
  Serial.println();
  Serial.println(io.statusText());


   
 //led setup
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p; // palette the led's automatically start on
    currentBlending = LINEARBLEND;

    
}


void loop() {
  io.run();
  // ChangePalettePeriodically();
    
    static uint8_t startIndex = 0;
   // startIndex = startIndex + 1; /* motion speed */
    
    FillLEDsFromPaletteColors( startIndex); // call & start function for coloring leds
    
    FastLED.show(); // display/light leds
    FastLED.delay(1000 / UPDATES_PER_SECOND);  
   
}

void paletteColorChanger(char* hexColor) {
  uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) { // 
        leds[i] = hexColor;
    }
}

void handleMessage(AdafruitIO_Data *data) {
  Serial.print("  - HEX: ");
  Serial.println(data->value());
  Serial.print("  - R: ");
  Serial.println(data->toRed());
  Serial.print("  - G: ");
  Serial.println(data->toGreen());
  Serial.print("  - B: ");
  Serial.println(data->toBlue());
 paletteColorChanger(data->value());
  }
 
void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) { // 
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}


/* 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
   OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
  Additionally, you can manually define your own color palettes, or you can write
  code that creates color palettes on the fly.  All are shown here. */

void ChangePalettePeriodically()
{
    uint8_t secondHand = (millis() / 1000) % 60; //timer
    static uint8_t lastSecond = 99;
    
     if( lastSecond != secondHand) {
        lastSecond = secondHand;
        if( secondHand ==  0)  { currentPalette = RainbowColors_p;         currentBlending = LINEARBLEND; }
        if( secondHand == 10)  { currentPalette = RainbowStripeColors_p;   currentBlending = NOBLEND;  }
        if( secondHand == 20)  { currentPalette = RainbowStripeColors_p;   currentBlending = LINEARBLEND; }
        if( secondHand == 30)  { currentPalette = OceanColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 40)  { currentPalette = LavaColors_p;            currentBlending = LINEARBLEND; }
        if( secondHand == 50)  { currentPalette = ForestColors_p;          currentBlending = LINEARBLEND; }
      //  if( secondHand == 35)  { SetupBlackAndWhiteStripedPalette();       currentBlending = LINEARBLEND; }
        if( secondHand == 60)  { currentPalette = CloudColors_p;           currentBlending = LINEARBLEND; }
        if( secondHand == 70)  { currentPalette = PartyColors_p;           currentBlending = LINEARBLEND; }
      //  if( secondHand == 50)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = NOBLEND;  }
       // if( secondHand == 55)  { currentPalette = myRedWhiteBluePalette_p; currentBlending = LINEARBLEND; }
    }
  }


