/*
  Photocell Light Meter Bar Graph Display 
  Reads a photocell on analog pin A0 and displays the brightness
  as a bar graph using 10 LEDs on digital pins 2–11.
*/

const int ldrPin = 0;            // Analog input from LDR voltage divider
const int firstLedPin = 2;        // First LED pin
const int lastLedPin = 11;       // Last LED pin (inclusive)
const int totalLeds = lastLedPin - firstLedPin; // Determine the total number of LEDs

void setup() {
  // Set LED pins as outputs
  for (int pin = firstLedPin; pin <= lastLedPin; pin++) {
    pinMode(pin, OUTPUT);
  }
}

void loop() {
  // Read the LDR (0–1023 from the analog-to-digital converter)
  int sensorValue = analogRead(ldrPin);

  // Convert sensor reading (0–1023) → bar level (0–10)
  int level = map(sensorValue, 0, 1023, 0, totalLeds);

  // Clamp level to valid range (0–10)
  level = constrain(level, 0, totalLeds);

  // Update LEDs: turn on only the first "level" LEDs
  for (int i = 0; i < totalLeds; i++) {
    int currentPin = firstLedPin + i;

    if (i < level) { //Check to see if current LED should be glowing based on the current light level
      digitalWrite(currentPin, HIGH);  // LED ON
    } else {
      digitalWrite(currentPin, LOW);   // LED OFF
    }
  }

  delay(50);  // Short delay to stabilize the display
}
