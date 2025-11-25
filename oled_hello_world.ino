/*
This sketch displays "Hello World!" on a 128x64 SSD1306 OLED display.
The address for the OLED is 0x3C
*/

// Load the libraries needed to support the OLED display
#include <SPI.h> // Loads support for SPI communication support. Required by many Adafruit libraries, even if SPI isn't used.
#include <Wire.h> // Loads support for I2C communication support.
#include <Adafruit_GFX.h> // Loads the Adafruit graphics core library. Used to plot points, draw shapes, draw text, etc.
#include <Adafruit_SSD1306.h>

const int SCREEN_WIDTH = 128; // OLED display width, in pixels
const int SCREEN_HEIGHT = 64; // OLED display height, in pixels
const int OLED_RESET = -1; // Sets the OLED display to reset when the Arduino Resets 
const int SCREEN_ADDRESS = 0x3C; // Stores the address to communite with the OLED display

//Create the OLED screen object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



void setup() {
  Serial.begin(9600);

  // Attempt to communicate with the OLED display and send a message over serial if you can't communicate.
  // SSD1306_SWITCHCAPVCC tells the display to use its built-in voltage booster so it can turn on pixels.
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();

  // Set text settings
  // display.setTextSize(2);       // Scale 2x
  display.setTextColor(SSD1306_WHITE); //Default text color is black (invisible). Set to SSD1306_WHITE so the text can be seen.
  display.setCursor(0, 10);     // X=0, Y=10

  // Write text to buffer
  display.println("Hello World!");

  // Send buffer to the display. Your text will not display until this statement is executed.
  display.display();
}

void loop() {
  // Everything ins this sketch only runs once, so  there is nothing to do here.
}