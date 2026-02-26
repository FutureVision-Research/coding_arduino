/* Sketch to control a relay with an Arduino Uno
 * This can be used to create a basic red light / green light game
 * The red LED should be connected to Normally Open on the relay
 * The green LED should be connected to Normally Closed on the relay
 * Written by Brian Cox
 * 5/29/2019
*/

// Precompiler directives are used here to set the pin definitions
#define BUTTON_PIN 10
#define RELAY_PIN 9

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize the relay pin as an output:
  pinMode(RELAY_PIN, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(BUTTON_PIN, INPUT_PULLUP); //Notice that we are using the built-in pullup resistor.
  }

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(BUTTON_PIN);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == LOW) {
    // Activate relay:
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    // Deactivate relay:
    digitalWrite(RELAY_PIN, LOW);
  }
}
