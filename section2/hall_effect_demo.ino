/* This sketch demonstrates the use of the US1881 Hall Effect Sensor.

This device sinks output (connects to ground) and holds that state (latches) when the sensor detects the South pole
of a magnet on the side of the device with the writing.

When the North pole is detected, the sensor releases the output, allowing it to go HIGH through the pull-up resistor.

Because the US1881 uses an open-collector output, it does not provide voltage itself — the pull-up resistor is required for a HIGH signal.

Keep in mind that the behavior is backwards if you expose the opposite side of the sensor to a magnetic field. 

Written by Brian Cox 11-26-25
*/
const int LEDPIN = 9;        //Set pin for LED
const int SENSORPIN = 12;    //Set pin for US1881 output
int sensorState = 1;         //Variable to record the state of the sensor

void setup() {
  pinMode(LEDPIN, OUTPUT);     //Set pin for LED as output
  pinMode(SENSORPIN, INPUT);   //Set pin for PIR sensor as input
}

void loop() {
  sensorState = digitalRead(SENSORPIN); //Read the state of the sensor pin
  
  if (sensorState == LOW){             //Cause the LED to glow if the sensor pin is low.  Otherwise, turn the LED off.
    digitalWrite(LEDPIN, HIGH);
  } else {
    digitalWrite(LEDPIN, LOW);
  }
}
