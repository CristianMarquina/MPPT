// These constants won't change. They're used to give names to the pins used:
const float analogVpvIn = A0;  // Analog input pin that the potentiometer is attached to
const float analogIpvPin = A1; // Analog output pin that the LED is attached to

float Vpvin = 0;        // Lectura del voltaje del arrglo
float Vpv= 0;
float Ipvin = 0;        //variables de lectura nueva
float Ipv= 0;
float Pv=0;
float dv=0;
float dp=0;
float di=0;
float D=0.6333;

float Ipva= 1;        // Variables anteriores
float Vpva= 1;
float Pva= Vpva*Ipva;


float VCC= 5;// Voltaje de alimentacion del sensor de corriente
float  sensitivity =0.100;// sensibilidad del ACS712ELCTR-20A-T
const float QOV =   0.5 * VCC;// set quiescent Output voltage of 0.5V
float voltage;// internal variable for voltage


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  // Lectura de voltaje y corriente
  
  Vpv=  (analogRead(analogVpvIn)*5.0*42.0)/1023.0;
  float voltage_raw =   (5.0 / 1023.0)* analogRead(analogIpvPin);// Read the voltage from sensor
  voltage =  voltage_raw - QOV + 0.012 ;// 0.000 is a value to make voltage zero when there is no current
  float Ipv = voltage / sensitivity;
  Pv= Ipv * Vpv;

  dv=Vpv-Vpva;
  di=Ipv-Ipva;
  dp=Pv-Pva;

  if(dp=0){
  D=D;
 }
 else{
  if(dp>0){
    if(dv>0){
      if(di>0){
        D=D+0.000001;
        }else{
          D=D-0.000001;
          }
      }else{
        D=D+0.000001;
        }
      
    }else if(dv>0){
      D=D+0.000001;
      }else {
        D=D-0.000001;
        } 
 }
  

  // change the analog out value:
  
  // print the results to the Serial Monitor:
  Serial.print("Vpv = ");
  Serial.print(Vpv);
  Serial.println("V");

   
  Serial.print("\t Ipv: ");
  Serial.print(Ipv,2); // print the current with 2 decimal places
  Serial.println("A");

  Serial.print("\t Pvp: ");
  Serial.print(Pv); // print the current with 2 decimal places
  Serial.println("W");

  Serial.print("Vpv anterior = ");
  Serial.print(Vpva);
  Serial.println("V");

   
  Serial.print("\t Ipv anterior: ");
  Serial.print(Ipva,2); // print the current with 2 decimal places
  Serial.println("A");

  Serial.print("\t Pvp anterior: ");
  Serial.print(Pva); // print the current with 2 decimal places
  Serial.println("W");

  Serial.print("\t D: ");
  Serial.print(D); 
  
  Pva=Pv;
  Vpva=Vpv;
  Ipva=Ipv;



  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(200);
}
