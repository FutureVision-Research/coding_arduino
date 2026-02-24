/*
  Simple Tone Example
  Speaker connected to digital pin 9.
  Plays two tones repeatedly.
*/

const int speakerPin = 9;

void setup() {
  // No setup required for tone()
}

void loop() {

  // Play first tone: 440 Hz (A4)
  tone(speakerPin, 440);   // Start tone at 440 Hz
  delay(500);              // Play for 500 milliseconds
  noTone(speakerPin);      // Stop tone
  delay(250);              // Short pause

  // Play second tone: 880 Hz (A5)
  tone(speakerPin, 880);   // Start tone at 880 Hz
  delay(500);              // Play for 500 milliseconds
  noTone(speakerPin);      // Stop tone
  delay(1000);             // Longer pause before repeating
}
