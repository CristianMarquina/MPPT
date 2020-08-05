// These constants won't change. They're used to give names to the pins used:
const float analogVpvIn = A0;  // Analog input pin that the potentiometer is attached to
const float analogOutPin = A5; // Analog output pin that the LED is attached to

float sensorValue = 0;        // value read from the pot
float outputValue = 0;      // value output to the PWM (analog out)
float voltage = 0;
void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogVpvIn);
  // map it to the range of the analog out:
 outputValue = 10.0/3.0;
  // change the analog out value:
  voltage =  (sensorValue*5.0)/1023.0;
  analogWrite(analogOutPin, outputValue);

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\t output = ");
  Serial.print(outputValue);
  Serial.print("\t vol = ");
  Serial.print(voltage);

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2000);
}
