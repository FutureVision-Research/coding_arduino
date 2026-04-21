// This sketch demonstrates how to receive input from the KY-040 Rotary Encoder
// This sketch does not receive input from the switch on the KY-040

// Pin connections
const int clkPin = 2;   // Used for the clock (CLK) pin on the rotary encoder
const int dtPin  = 3;   // Used for the data (DT) pin on the rotary encoder

int counter = 0;        // This will change as you turn the knob
int lastCLKState;       // Used to keep track of the state of CLK

void setup() {
  // Set both pins as inputs
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);

  Serial.begin(9600);

  // Read the starting state of CLK
  lastCLKState = digitalRead(clkPin);
}

void loop() {
  int currentCLKState = digitalRead(clkPin); // Reads the state of the pin for CLK

  // Detect a change in the CLK signal
  if (currentCLKState != lastCLKState && currentCLKState == HIGH) {

    // Check direction
    if (digitalRead(dtPin) != currentCLKState) {
      counter++;   // Turned one way
      Serial.println("Clockwise");
    } else {
      counter--;   // Turned the other way
      Serial.println("Counterclockwise");
    }

    // Show the current value
    Serial.print("Counter: ");
    Serial.println(counter);
  }

  // Save the current state for next loop
  lastCLKState = currentCLKState;
}
