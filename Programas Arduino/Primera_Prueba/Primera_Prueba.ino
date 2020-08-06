// These constants won't change. They're used to give names to the pins used:
const float analogVpvIn = A0;  // Analog input pin that the potentiometer is attached to
const float analogIpvPin = A1; // Analog output pin that the LED is attached to

float Vpvin = 0;        // Lectura del voltaje del arrglo
float Vpv= 0;
float sensorValue=0;

float Ipvin = 0;        //Lectura de la corriente del arreglo
float Ipv= 0;

float VCC= 5;// Voltaje de alimentacion del sensor de corriente
float  sensitivity =0.100;// sensibilidad del ACS712ELCTR-20A-T
const float QOV =   0.5 * VCC;// set quiescent Output voltage of 0.5V
float voltage;// internal variable for voltage


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // Lectura de voltaje
  sensorValue = analogRead(analogVpvIn);
  Vpv=  (sensorValue*5.0*42.0)/1023.0;


  
  float voltage_raw =   (5.0 / 1023.0)* analogRead(analogIpvPin);// Read the voltage from sensor
  voltage =  voltage_raw - QOV + 0.012 ;// 0.000 is a value to make voltage zero when there is no current
  float current = voltage / sensitivity;
 

  // change the analog out value:
  
  // print the results to the Serial Monitor:
  Serial.print("Vpv = ");
  Serial.print(Vpv);
  Serial.println("V");

   
  Serial.print("\t Ipv: ");
  Serial.print(current,2); // print the current with 2 decimal places
  Serial.println("A");

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(2000);
}
