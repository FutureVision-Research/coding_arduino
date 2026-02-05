// This sketch demonstrates how to use a function
void setup() {
  Serial.begin(9600);
}

int add(int a, int b) {
  int result = a + b;
  return result;
}

void loop() {
  int answer = add(5,8);
  Serial.print("The sum of your two numbers is ");
  Serial.println(answer);
  delay(5000);
}
