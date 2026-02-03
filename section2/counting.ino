// This sketch demonstrates how to use a for() loop.
void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Start at 0 and count to 4");
  for (int i = 0; i < 5; i++) {
    Serial.println(i);
    delay(1000);
  }

  delay(2000);  // wait 2 seconds before continuing

  Serial.println("Start at 4 and count down to 0");
  for (int i = 4; i>=0; i--) {
    Serial.println(i);
    delay(1000);
  }  

  delay(2000);  // wait 2 seconds before continuing

  Serial.println("Start at 0 and count by 2's up to 10");
  for (int i = 0; i<=10; i+=2) {  // Using i+=2 is the same as saying i = i + 2
    Serial.println(i);
    delay(1000);
  }  

  delay(2000);  // wait 2 seconds before continuing
}
