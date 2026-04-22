#include <Adafruit_NeoPixel.h>

// --------------------------------------------------
// NeoPixel settings
// --------------------------------------------------
// The NeoPixel data wire is connected to pin 6.
const int pixelPin = 6;

// We have 5 NeoPixels in the strand.
const int numberOfPixels = 5;

// Create the NeoPixel object.
// The strand uses GRB color order and 800 KHz timing.
Adafruit_NeoPixel strip(numberOfPixels, pixelPin, NEO_GRB + NEO_KHZ800);

// --------------------------------------------------
// KY-040 rotary encoder pins
// --------------------------------------------------
// CLK and DT are the two encoder output pins.
// SW is the pushbutton switch built into the encoder.
const int encoderCLK = 2;
const int encoderDT  = 3;
const int encoderSW  = 4;

// --------------------------------------------------
// Program states
// --------------------------------------------------
/*
  enum is short for "enumeration."

  An enumeration lets us create a small list of named values.

  In this sketch, we use enum to give names to the three modes
  of operation. This makes the code easier to read than using
  plain numbers like 0, 1, and 2.

  IDLE         = the sketch is waiting for the first button press
  SELECT_PIXEL = the encoder chooses which NeoPixel to edit
  SELECT_COLOR = the encoder chooses the new color
*/
enum Mode
{
  IDLE,
  SELECT_PIXEL,
  SELECT_COLOR
};

// This variable stores the current mode.
Mode currentMode = IDLE;

// --------------------------------------------------
// Pixel color storage
// --------------------------------------------------
/*
  Each NeoPixel color is stored as a single number.

  Even though a color is made from red, green, and blue values,
  the Adafruit library combines those values into one long number.

  We use unsigned long here because it is a classic Arduino type
  and works well for storing the color value returned by strip.Color().
*/
unsigned long pixelColors[numberOfPixels];

// --------------------------------------------------
// Selection variables
// --------------------------------------------------
// Which pixel is currently selected
int selectedPixel = 0;

// Which color from our list is currently selected
int selectedColorIndex = 0;

// We want 10 evenly spaced colors around the color wheel
const int numberOfColors = 10;

// --------------------------------------------------
// Encoder and button tracking
// --------------------------------------------------
// This stores the previous CLK reading so we can detect change
int lastCLKState;

// Last reading from the pushbutton
bool lastButtonState = HIGH;

// Used for simple button debouncing
unsigned long lastButtonChangeTime = 0;
const unsigned long debounceDelay = 30;

// --------------------------------------------------
// Blink timing
// --------------------------------------------------
// blinkState changes from true to false so the selected pixel blinks
bool blinkState = true;

// Used to measure time between blinks
unsigned long lastBlinkTime = 0;
const unsigned long blinkInterval = 300;

// --------------------------------------------------
// Function declarations
// --------------------------------------------------
void showAllRed();
void handleEncoder();
void handleButton();
void updateDisplay();
unsigned long getColorFromIndex(int index);

void setup()
{
  // Set the encoder pins as inputs
  pinMode(encoderCLK, INPUT);
  pinMode(encoderDT, INPUT);

  // Use the internal pull-up resistor for the button
  // This means:
  // not pressed = HIGH
  // pressed     = LOW
  pinMode(encoderSW, INPUT_PULLUP);

  // Start the NeoPixel strip
  strip.begin();
  strip.show();

  // Start with all pixels red
  showAllRed();

  // Read the starting state of the CLK pin
  lastCLKState = digitalRead(encoderCLK);
}

void loop()
{
  // Check for encoder movement
  handleEncoder();

  // Check for button presses
  handleButton();

  // If we are in a selection mode, make the selected pixel blink
  if (currentMode == SELECT_PIXEL || currentMode == SELECT_COLOR)
  {
    if (millis() - lastBlinkTime >= blinkInterval)
    {
      lastBlinkTime = millis();
      blinkState = !blinkState;
      updateDisplay();
    }
  }
}

// --------------------------------------------------
// Set all NeoPixels to red at the beginning
// --------------------------------------------------
void showAllRed()
{
  for (int i = 0; i < numberOfPixels; i++)
  {
    pixelColors[i] = strip.Color(255, 0, 0);
  }

  updateDisplay();
}

// --------------------------------------------------
// Read the rotary encoder
// --------------------------------------------------
void handleEncoder()
{
  int currentCLKState = digitalRead(encoderCLK);

  // We look for a change on CLK.
  // We only react when CLK becomes HIGH.
  // This helps reduce extra counts.
  if (currentCLKState != lastCLKState && currentCLKState == HIGH)
  {
    // Compare DT to CLK to determine direction
    if (digitalRead(encoderDT) != currentCLKState)
    {
      // Clockwise turn

      if (currentMode == SELECT_PIXEL)
      {
        selectedPixel++;

        // Wrap around to the beginning
        if (selectedPixel >= numberOfPixels)
        {
          selectedPixel = 0;
        }
      }
      else if (currentMode == SELECT_COLOR)
      {
        selectedColorIndex++;

        // Wrap around to the beginning
        if (selectedColorIndex >= numberOfColors)
        {
          selectedColorIndex = 0;
        }
      }
    }
    else
    {
      // Counterclockwise turn

      if (currentMode == SELECT_PIXEL)
      {
        selectedPixel--;

        // Wrap around to the end
        if (selectedPixel < 0)
        {
          selectedPixel = numberOfPixels - 1;
        }
      }
      else if (currentMode == SELECT_COLOR)
      {
        selectedColorIndex--;

        // Wrap around to the end
        if (selectedColorIndex < 0)
        {
          selectedColorIndex = numberOfColors - 1;
        }
      }
    }

    updateDisplay();
  }

  // Save this reading for next time through the loop
  lastCLKState = currentCLKState;
}

// --------------------------------------------------
// Read the pushbutton on the encoder
// --------------------------------------------------
void handleButton()
{
  bool currentButtonState = digitalRead(encoderSW);

  // If the button reading changed, reset the debounce timer
  if (currentButtonState != lastButtonState)
  {
    lastButtonChangeTime = millis();
  }

  // Wait a short time so button bouncing settles down
  if (millis() - lastButtonChangeTime > debounceDelay)
  {
    // Detect a button press: HIGH to LOW
    if (lastButtonState == HIGH && currentButtonState == LOW)
    {
      if (currentMode == IDLE)
      {
        // First click:
        // start selecting pixels
        selectedPixel = 0;
        currentMode = SELECT_PIXEL;
        blinkState = true;
        updateDisplay();
      }
      else if (currentMode == SELECT_PIXEL)
      {
        // Second click:
        // choose a color for the blinking pixel
        currentMode = SELECT_COLOR;
        selectedColorIndex = 0;
        blinkState = true;
        updateDisplay();
      }
      else if (currentMode == SELECT_COLOR)
      {
        // Third click:
        // save the chosen color into the selected pixel
        pixelColors[selectedPixel] = getColorFromIndex(selectedColorIndex);

        // Return to pixel selection mode
        currentMode = SELECT_PIXEL;
        blinkState = true;
        updateDisplay();
      }
    }
  }

  // Save this reading for next time through the loop
  lastButtonState = currentButtonState;
}

// --------------------------------------------------
// Return one of 10 evenly spaced colors
// --------------------------------------------------
unsigned long getColorFromIndex(int index)
{
  /*
    ColorHSV() creates colors using hue.

    Hue is the position around the color wheel.
    We divide the wheel into 10 equal parts.

    gamma32() helps the colors look more natural to our eyes.
  */
  unsigned long hue = (65535UL * index) / numberOfColors;
  return strip.gamma32(strip.ColorHSV(hue));
}

// --------------------------------------------------
// Update what the NeoPixels display
// --------------------------------------------------
void updateDisplay()
{
  // First, show all saved pixel colors
  for (int i = 0; i < numberOfPixels; i++)
  {
    strip.setPixelColor(i, pixelColors[i]);
  }

  if (currentMode == SELECT_PIXEL)
  {
    // In pixel selection mode,
    // the selected pixel blinks on and off
    if (!blinkState)
    {
      strip.setPixelColor(selectedPixel, 0);
    }
  }
  else if (currentMode == SELECT_COLOR)
  {
    // In color selection mode,
    // the selected pixel blinks using the preview color
    if (blinkState)
    {
      strip.setPixelColor(selectedPixel, getColorFromIndex(selectedColorIndex));
    }
    else
    {
      strip.setPixelColor(selectedPixel, 0);
    }
  }

  strip.show();
}
