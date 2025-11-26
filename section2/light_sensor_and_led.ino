/*
Light Sensor and LED
Use a photoresistor (light sensor) to control the brightness of a LED.
*/

// As usual, we'll create constants to name the pins we're using.

const int SENSOR_Pin = 0; // When used with analogRead() the number 0 represents pin A0
const int LED_PIN = 9; // We use pin 9 because it supports PWM

// Declare three variables that will change.
// This provides an example of declaring variables of the same type on one line.

int lightLevel, high = 0, low = 1023;

void setup()
{
  // Set the mode of the LED's pin as an output

  pinMode(LED_PIN, OUTPUT);
} //This is the end of the setup() function

// In this section, we create two functions: manualTune() and autoTune().
// We will call these functions inside Loop(). Officially functions should be created before you call them.

// This function uses map() and constrain() to adjust the analog range of 0 to 1023 to the PWM range of 0 to 255
void manualTune() 
{ 
  // The light circuit most likely will not provide a full range of 0 - 1023. 
  // Feel free to experiement with those two numbers so the LED will glow the full range from off to full brightness
  
  lightLevel = map(lightLevel, 0, 1023, 0, 255);
  lightLevel = constrain(lightLevel, 0, 255);

} //This is the end of the manualTune() function 

void autoTune()
{
  // The light circuit most likely will not provide a full range of 0 - 1023. 
  // This function checks the possible range and adjusts the input values.
  // This allows the LED to go from dark to full brightness.

  if (lightLevel < low)
  {
    low = lightLevel;
  }

  // We also initialized "high" to be 0. We'll save anything
  // we read that's higher than that:

  if (lightLevel > high)
  {
    high = lightLevel;
  }

  // Once we have the highest and lowest values, we can stick them
  // directly into the map() function. No manual tweaking needed!

  // One trick we'll do is to add a small offset to low and high,
  // to ensure that the LED is fully-off and fully-on at the limits
  // (otherwise it might flicker a little bit).

  lightLevel = map(lightLevel, low+30, high-30, 0, 255);
  lightLevel = constrain(lightLevel, 0, 255);
} //This is the end of the autoTune() function

void loop()
{
  // Take an analog reading 

  lightLevel = analogRead(SENSOR_Pin);

  // Only call one of these two functions. The other function should remain as a comment so it won't be called.

  manualTune();  // manually change the range from light to dark

  //autoTune();  // have the Arduino do the work for us!

  // Once you call the function, the sketch will return to this point.
  // The following statement takes the final value from the manualTune() or autoTune() function and sends it as a PWM value to the LED
  analogWrite(LED_PIN, lightLevel);
  
} // This is the end of the loop() function
