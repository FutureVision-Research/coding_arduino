/*LED sequencer sketch 
Updated 2/3/2026
by Brian P. Cox, FutureVision Research
Sketch is under Creative Commmons License Attribution-NonCommercial-ShareAlike 4.0 International
*/


const int FIRST_LED_PIN = 2, LAST_LED_PIN = 11; // Specifiy the first and last LED pins

// Declare variables
int sequenceSpeed = 100; //This is the delay between lighting LEDs. Recommend a value between 10 and 1000


void setup() { //Setup function runs once
  for (int counter = FIRST_LED_PIN; counter <= LAST_LED_PIN; counter++) {  //Set all LED pins as outputs
    pinMode(counter,OUTPUT);
    } //End of counter
}//End of setup() function

void classicSequencer(){ //Lignt one LED at a time from left to right
  for(int counter = FIRST_LED_PIN; counter <= LAST_LED_PIN; ++counter) { //counter used to keep track of LED sequence
    digitalWrite(counter, HIGH);
    delay(sequenceSpeed);
    digitalWrite(counter, LOW);
    }//End of counter
}//End of classicSequencer function

// This section creates functions for the various types of LED sequencers.
// We will then call the specific function we want to run. 
void oneAfterAnother(){ //Light one LED after another then turn each one off
    for(int counter = FIRST_LED_PIN; counter <= LAST_LED_PIN; ++counter) { 
      delay(sequenceSpeed);
      digitalWrite(counter, HIGH);
      delay(sequenceSpeed);   
    }
    for(int counter = LAST_LED_PIN; counter >= FIRST_LED_PIN; --counter) {
      delay(sequenceSpeed);
      digitalWrite(counter, LOW);
      delay(sequenceSpeed);   
    }         
}//End of oneAfterAnother function

void pingPong(){
  delay(sequenceSpeed);
  for(int counter = FIRST_LED_PIN; counter <= LAST_LED_PIN; ++counter) {//Light one LED at a time from left to right
    digitalWrite(counter, HIGH);  // turn LED on
    delay(sequenceSpeed);         // pause to slow down
    digitalWrite(counter, LOW);   // turn LED off
  }

  delay(sequenceSpeed);
  for(int counter = LAST_LED_PIN; counter >= FIRST_LED_PIN; --counter) { //Light one LED at a time from right to left
    digitalWrite(counter, HIGH);  // turn LED on
    delay(sequenceSpeed);         // pause to slow down
    digitalWrite(counter, LOW);   // turn LED off
  }
}//End of pingPong function

void randomLED(){
  delay(sequenceSpeed);
  int randomNumber = random(FIRST_LED_PIN,LAST_LED_PIN+1);  // pick a LED pin within the proper range
  digitalWrite(randomNumber, HIGH);  // turn LED on
  delay(sequenceSpeed);              // pause to slow down
  digitalWrite(randomNumber, LOW);   // turn LED off
}


void loop() { //Loop function runs over and over
  //The next four lines call four different functions, each light the LEDs in a pattern.
  //Leave all but one commented. The line that remains uncommented will be called.

  classicSequencer();
  //oneAfterAnother();
  //pingPong();
  //randomLED();

}//End of loop function  
