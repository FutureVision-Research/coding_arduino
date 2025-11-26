//TMP36 sample sketch

//Declare a constant to store the pin number for the analog input
const int SENSOR_PIN = 0; //When used with analogRead(), a 0 represents A0

void setup()
{
  Serial.begin(9600);  //Start the serial connection with the computer.
  // This allows us to view the resulting temperature in the Serial Monitor  
}
 
void loop()                  
{
 // declares a variable called reading and stores the analog reading from the TMP36
 int reading = analogRead(SENSOR_PIN);  
 
 // The TMP36 varies it input voltage to provide a temperature reading
 // We are using an Arduino Uno, so the supply voltage is 5V.
 // analogRead() returns a value between 0 and 1023.
 // This calculation converts the analog reading to a voltage.
 float voltage = reading * 5;
 voltage /= 1024.0; 
 
 // print out the voltage
 Serial.print(voltage); Serial.println(" volts");
 
 // now print out the temperature
 float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 Serial.print(temperatureC); Serial.println(" degrees C");
 
 // now convert to Fahrenheit
 float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
 Serial.print(temperatureF); Serial.println(" degrees F");
 
 delay(1000);                                     //waiting a second
}