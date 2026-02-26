/* motor speed controller
 * Written by Brian Cox
 * 5/29/2019
*/

// variables that will not change
const int MOTOR_PIN = 3; // This pin will be used to control the motor. It must be a pin that can support PWM

// variables will change:
int voltageDivider = 0;         // Variable to store the value of the voltage divider
int pwmValue = 0;               // Variable to store the result of the conversion from the voltage divider value

void setup() {
  pinMode(MOTOR_PIN, OUTPUT); // Initialize the motor pin as an output
}

void loop() {
  voltageDivider = analogRead(A0); // Read the value of the voltage divider
  // We use a PWM range of 100 to 255 because if we send lower than 100, the motor may not spin.
  pwmValue = map(voltageDivider, 0, 1023, 100, 255); // Convert the range from the voltage divider to the range used for PWM output
  pwmValue = constrain(pwmValue, 100, 255); // Ensures that the variable will stay within the proper range
  analogWrite(MOTOR_PIN, pwmValue); // Send the coverted value out to the pin as PWM
}
