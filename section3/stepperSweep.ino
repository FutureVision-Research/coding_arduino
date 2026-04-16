// This sketch demontrates how to sweep a stepper motor back and forth

#include <Stepper.h>    //Loads library for stepper motor support

//Set variables for the four stepper motor pins
int in1Pin = 12;
int in2Pin = 11;
int in3Pin = 10;
int in4Pin = 9;

//Create the stepper motor object. First argument is the number of steps the motors needs for one full rotation.
Stepper motor(512, in1Pin, in2Pin, in3Pin, in4Pin);

void setup(){
  // Set all four stepper motor pins as outputs
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
 
  // Set speed for the motor in Rotations Per Minute (RPM)
  motor.setSpeed(20);
}
void loop(){
  motor.step(256); //Rotates the stepper in a half circle one direction
  motor.step(-256); //Rotates the stepper the other direction
}// End of loop