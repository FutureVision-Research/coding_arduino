//This sketch helps you test if your WS2812 LEDs are configured for RGB or GRB

#include <Adafruit_NeoPixel.h>

// Pin and pixel count
#define PIN 6
#define NUM_PIXELS 5

//LEDs should glow red, then green, then blue.
//If they don't change NEO_RGB to NEO_GRB in the following statement
//Then anytime you use the Adafruit_NeoPixel library, you will use NEO_GRB

Adafruit_NeoPixel strip(NUM_PIXELS, PIN, NEO_RGB + NEO_KHZ800);

void setup()
{
  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to off
}

void loop()
{
  // Test RED
  for (int i = 0; i < NUM_PIXELS; i++)
  {
    strip.setPixelColor(i, strip.Color(255, 0, 0));
  }
  strip.show();
  delay(2000);

  // Test GREEN
  for (int i = 0; i < NUM_PIXELS; i++)
  {
    strip.setPixelColor(i, strip.Color(0, 255, 0));
  }
  strip.show();
  delay(2000);

  // Test BLUE
  for (int i = 0; i < NUM_PIXELS; i++)
  {
    strip.setPixelColor(i, strip.Color(0, 0, 255));
  }
  strip.show();
  delay(2000);
}
