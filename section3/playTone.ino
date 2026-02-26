/*
  Tone Demonstration with Frequency Sweep
  Speaker connected to digital pin 9 through a 2N2222 transistor.
*/

const int speakerPin = 9;

void setup() {
  // No setup required this sketch
}

void loop() {

  // --- Generate a tone at 440 Hz ---
  tone(speakerPin, 440);
  delay(500);
  noTone(speakerPin);
  delay(250);

  // --- Generate a tone at 880 Hz ---
  tone(speakerPin, 880);
  delay(500);
  noTone(speakerPin);
  delay(1000);

  // --- Frequency sweep from 440 Hz to 880 Hz ---
  for (int freq = 440; freq <= 880; freq += 10) {
    tone(speakerPin, freq);   // Update frequency
    delay(50);                // Short duration per step
  }

  // --- Frequency sweep from 440 Hz to 880 Hz ---
  for (int freq = 880; freq >= 440; freq -= 10) {
    tone(speakerPin, freq);   // Update frequency
    delay(50);                // Short duration per step
  }

  noTone(speakerPin);         // Stop tone after sweep
  delay(2000);                // Pause before repeating
}
