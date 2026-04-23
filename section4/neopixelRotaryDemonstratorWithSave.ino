#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

// --------------------------------------------------
// NeoPixel settings
// --------------------------------------------------
const int pixelPin = 6;
const int numberOfPixels = 5;

// Create the NeoPixel object
Adafruit_NeoPixel strip(numberOfPixels, pixelPin, NEO_GRB + NEO_KHZ800);

// --------------------------------------------------
// KY-040 rotary encoder pins
// --------------------------------------------------
const int encoderCLK = 2;
const int encoderDT  = 3;
const int encoderSW  = 4;

// --------------------------------------------------
// EEPROM settings
// --------------------------------------------------
// We store a signature value so the sketch can tell
// whether valid color data has been saved before.
const int eepromSignatureAddress = 0;
const unsigned long eepromSignatureValue = 123456789;

// The pixel color data is stored after the signature.
const int eepromDataAddress = sizeof(unsigned long);

// --------------------------------------------------
// enum means enumeration
// It lets us create a list of named values.
// This makes the program easier to read.
// --------------------------------------------------
enum Mode
{
  IDLE,
  SELECT_PIXEL,
  SELECT_COLOR
};

// This variable stores the current mode
Mode currentMode = IDLE;

// --------------------------------------------------
// Array to store the saved color of each NeoPixel
// --------------------------------------------------
unsigned long pixelColors[numberOfPixels];

// --------------------------------------------------
// Selection variables
// --------------------------------------------------
int selectedPixel = 0;
int selectedColorIndex = 0;

// Number of available colors
const int numberOfColors = 10;

// --------------------------------------------------
// Encoder tracking
// --------------------------------------------------
int lastCLKState;

// --------------------------------------------------
// Button variables
// --------------------------------------------------
bool buttonReading = HIGH;
bool lastButtonReading = HIGH;
bool buttonState = HIGH;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 30;

// These variables are used to detect a long press
unsigned long buttonPressStartTime = 0;
bool longPressHandled = false;
const unsigned long longPressTime = 1000;

// --------------------------------------------------
// Blink timing
// --------------------------------------------------
bool blinkState = true;
unsigned long lastBlinkTime = 0;
const unsigned long blinkInterval = 300;

// --------------------------------------------------
// Function declarations (prototypes)
// These list the functions used in this program.
// The full definitions are written later in the file.
// --------------------------------------------------
void showAllRed();
void handleEncoder();
void handleButton();
void updateDisplay();
unsigned long getColorFromIndex(int index);
void processShortPress();
void processLongPress();
int findColorIndex(unsigned long targetColor);
void saveColorsToEEPROM();
bool loadColorsFromEEPROM();

void setup()
{
  pinMode(encoderCLK, INPUT);
  pinMode(encoderDT, INPUT);
  pinMode(encoderSW, INPUT_PULLUP);

  strip.begin();

  // Set overall brightness
  strip.setBrightness(50);

  strip.show();

  // If valid saved colors are found in EEPROM, use them.
  // Otherwise, start with all pixels glowing red.
  if (!loadColorsFromEEPROM())
  {
    showAllRed();
  }
  else
  {
    updateDisplay();
  }

  lastCLKState = digitalRead(encoderCLK);

  buttonReading = digitalRead(encoderSW);
  lastButtonReading = buttonReading;
  buttonState = buttonReading;
}

void loop()
{
  handleEncoder();
  handleButton();

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
// Set all pixels to red
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
// Read rotary encoder movement
// --------------------------------------------------
void handleEncoder()
{
  int currentCLKState = digitalRead(encoderCLK);

  if (currentCLKState != lastCLKState && currentCLKState == HIGH)
  {
    if (digitalRead(encoderDT) != currentCLKState)
    {
      // Clockwise turn
      if (currentMode == SELECT_PIXEL)
      {
        selectedPixel++;

        if (selectedPixel >= numberOfPixels)
        {
          selectedPixel = 0;
        }
      }
      else if (currentMode == SELECT_COLOR)
      {
        selectedColorIndex++;

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

        if (selectedPixel < 0)
        {
          selectedPixel = numberOfPixels - 1;
        }
      }
      else if (currentMode == SELECT_COLOR)
      {
        selectedColorIndex--;

        if (selectedColorIndex < 0)
        {
          selectedColorIndex = numberOfColors - 1;
        }
      }
    }

    updateDisplay();
  }

  lastCLKState = currentCLKState;
}

// --------------------------------------------------
// Read and debounce the pushbutton
// Also detect short press and long press
// --------------------------------------------------
void handleButton()
{
  buttonReading = digitalRead(encoderSW);

  if (buttonReading != lastButtonReading)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    if (buttonReading != buttonState)
    {
      buttonState = buttonReading;

      // Button has just been pressed
      if (buttonState == LOW)
      {
        buttonPressStartTime = millis();
        longPressHandled = false;
      }

      // Button has just been released
      if (buttonState == HIGH)
      {
        if (!longPressHandled)
        {
          processShortPress();
        }
      }
    }
  }

  if (buttonState == LOW && !longPressHandled)
  {
    if (millis() - buttonPressStartTime >= longPressTime)
    {
      processLongPress();
      longPressHandled = true;
    }
  }

  lastButtonReading = buttonReading;
}

// --------------------------------------------------
// Handle a normal short press
// --------------------------------------------------
void processShortPress()
{
  if (currentMode == IDLE)
  {
    // First short press enters pixel selection mode
    selectedPixel = 0;
    currentMode = SELECT_PIXEL;
    blinkState = true;
    updateDisplay();
  }
  else if (currentMode == SELECT_PIXEL)
  {
    // Next short press enters color selection mode
    currentMode = SELECT_COLOR;

    // Start from this pixel's current saved color
    selectedColorIndex = findColorIndex(pixelColors[selectedPixel]);

    blinkState = true;
    updateDisplay();
  }
  else if (currentMode == SELECT_COLOR)
  {
    // Save the chosen color to the selected pixel
    pixelColors[selectedPixel] = getColorFromIndex(selectedColorIndex);

    // Save the new colors to EEPROM
    saveColorsToEEPROM();

    // Return to pixel selection mode
    currentMode = SELECT_PIXEL;
    blinkState = true;
    updateDisplay();
  }
}

// --------------------------------------------------
// Handle a long press
// --------------------------------------------------
void processLongPress()
{
  if (currentMode == SELECT_COLOR)
  {
    pixelColors[selectedPixel] = getColorFromIndex(selectedColorIndex);

    // Save the new colors to EEPROM
    saveColorsToEEPROM();
  }

  currentMode = IDLE;
  blinkState = true;
  updateDisplay();
}

// --------------------------------------------------
// Return one of 10 evenly spaced colors
// --------------------------------------------------
unsigned long getColorFromIndex(int index)
{
  unsigned long hue = (65535UL * index) / numberOfColors;
  return strip.gamma32(strip.ColorHSV(hue));
}

// --------------------------------------------------
// Find which color index matches a saved pixel color
// --------------------------------------------------
int findColorIndex(unsigned long targetColor)
{
  for (int i = 0; i < numberOfColors; i++)
  {
    if (getColorFromIndex(i) == targetColor)
    {
      return i;
    }
  }

  return 0;
}

// --------------------------------------------------
// Save the current pixel colors to EEPROM
// --------------------------------------------------
void saveColorsToEEPROM()
{
  // Write the signature first
  EEPROM.put(eepromSignatureAddress, eepromSignatureValue);

  // Write each pixel color after the signature
  for (int i = 0; i < numberOfPixels; i++)
  {
    int address = eepromDataAddress + (i * sizeof(unsigned long));
    EEPROM.put(address, pixelColors[i]);
  }
}

// --------------------------------------------------
// Load saved pixel colors from EEPROM
// Returns true if valid data was found
// Returns false if no valid saved data was found
// --------------------------------------------------
bool loadColorsFromEEPROM()
{
  unsigned long storedSignature;

  EEPROM.get(eepromSignatureAddress, storedSignature);

  if (storedSignature != eepromSignatureValue)
  {
    return false;
  }

  for (int i = 0; i < numberOfPixels; i++)
  {
    int address = eepromDataAddress + (i * sizeof(unsigned long));
    EEPROM.get(address, pixelColors[i]);
  }

  return true;
}

// --------------------------------------------------
// Update the NeoPixel display
// --------------------------------------------------
void updateDisplay()
{
  for (int i = 0; i < numberOfPixels; i++)
  {
    strip.setPixelColor(i, pixelColors[i]);
  }

  if (currentMode == SELECT_PIXEL)
  {
    if (!blinkState)
    {
      strip.setPixelColor(selectedPixel, 0);
    }
  }
  else if (currentMode == SELECT_COLOR)
  {
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
