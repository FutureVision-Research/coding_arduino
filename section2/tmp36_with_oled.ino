// TMP36 to OLED Display Example
// Uses Adafruit SSD1306 library on a 128x64 OLED
// TMP36 connected to analog pin A0

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Create constants that contain the particulars for the display.
const int SCREEN_WIDTH = 128; // OLED display width, in pixels
const int SCREEN_HEIGHT = 64; // OLED display height, in pixels
const int OLED_RESET = -1; // Sets the OLED display to reset when the Arduino Resets 
const int SCREEN_ADDRESS = 0x3C; // Stores the address to communite with the OLED display

// Define the Analog pin for TMP36
const int SENSOR_PIN = 0; // When used with analogRead(), 0 represents A0.

//Create the OLED screen object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



void setup() {
  // Initialize display and stop the script if it fails to initialize.
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Most 128x64 OLEDs use 0x3C
    for(;;); // Stop if display fails to initialize
  }

  // Prepares the display. This only needs to happen once.
  display.clearDisplay();
  display.setTextSize(2);         // Larger readable text
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  // Read TMP36 sensor
  int reading = analogRead(SENSOR_PIN);
  
  // The TMP36 varies it input voltage to provide a temperature reading
  // We are using an Arduino Uno, so the supply voltage is 5V.
  // analogRead() returns a value between 0 and 1023.
  // This calculation converts the analog reading to a voltage.
  float voltage = (reading * 5.0) / 1023.0;

  // The TMP36 outputs 0.5 volts at 0°C
  // Every additional 10 millivolts (0.01 V) equals 1°C
 
  // To determine the temperature:
  // Start with the voltage reading and subtract .5 volts because that represents 0°C.
  // Then multiply by 100 to get the temperature in Celsius.
  float temperatureC = (voltage - 0.5) * 100.0;
  // Convert the temperature to Fahrenheit
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;

  // Display readings on OLED
  display.clearDisplay();
  display.setCursor(0, 0); // Starts at top left corner of the display

  display.print("Temp:"); // Writes the word Temp: on the display because it is in quotes.
  display.setCursor(0, 20); // Moves the cursor to a new position to the next output doen't overlap the previous information.
  
  // The following statement writes the value of the variable temperatureC.
  // The 1 tells the function how many digits to show after the decimal point.
  // To output the value of a variable, provide the variable name without quotes.
  display.print(temperatureC, 1); 
  display.print(" C");

  display.setCursor(0, 40);

  // The following statement writes the value of the variable temeratureF.
  // The 1 tells the function how many digits to show after the decimal point.
  // To output the value of a variable, provide the variable name without quotes.
  display.print(temperatureF, 1);
  display.print(" F");

  display.display(); //Sends the previous information from the screen's buffer to the display.
  delay(1000);
}
