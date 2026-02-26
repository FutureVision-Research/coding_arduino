/*
  Photocell Light Meter Bar Graph Display 
  Reads a photocell on analog pin A0 and displays the brightness
  as a bar graph using 10 LEDs on digital pins 2–11.
*/

const int PHOTOCELL_PIN = 0; // Analog input from LDR voltage divider
const int FIRST_LED_PIN = 2; // First LED pin
const int LAST_LED_PIN = 11; // Last LED pin (inclusive)
const int TOTAL_LEDS = LAST_LED_PIN - FIRST_LED_PIN; // This variable isn't used. It demonstrates how to determine the total number of LEDs. But will the count be correct?
// const int TOTAL_LEDS = (LAST_LED_PIN - FIRST_LED_PIN) + 1; This would be the proper way to get an accurate count.

void setup() {
  // Set LED pins as outputs
  for (int pin = FIRST_LED_PIN; pin <= LAST_LED_PIN; pin++) {
    pinMode(pin, OUTPUT);
  }
}

void loop() {
  // Read the LDR (0–1023 from the analog-to-digital converter)
  int sensorValue = analogRead(PHOTOCELL_PIN);

  // Convert sensor reading (0–1023) → bar level (0–10)
  int level = map(sensorValue, 0, 1023, 0, TOTAL_LEDS);

  // Clamp level to valid range (0–10)
  level = constrain(level, 0, TOTAL_LEDS);

  // Update LEDs: turn on only the first "level" LEDs
  for (int i = 0; i < TOTAL_LEDS; i++) {
    int currentPin = FIRST_LED_PIN + i;

    if (i < level) { //Check to see if current LED should be glowing based on the current light level
      digitalWrite(currentPin, HIGH);  // LED ON
    } else {
      digitalWrite(currentPin, LOW);   // LED OFF
    }
  }

  delay(50);  // Short delay to stabilize the display
}
