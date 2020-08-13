const float analogVpvIn = A0;  // Analog input pin that the potentiometer is attached to
const float analogIpvPin = A1; // Analog output pin that the LED is attached to
float D=0.093;

float T=666.66;

float Vpvin = 0;        // Lectura del voltaje del arrglo
float Vpv= 0;
float Ipvin = 0;        //variables de lectura nueva
float Ipv= 0;
float Pv=0;
float dv=0;
float dp=0;
float di=0;

float voltage=0;
float voltage_raw=0;
float VCC= 5;// Voltaje de alimentacion del sensor de corriente
float  sensitivity =0.100;// sensibilidad del ACS712ELCTR-20A-T
const float QOV =   0.5 * VCC;// set quiescent Output voltage of 0.5V




float Ipva= 1;        // Variables anteriores
float Vpva= 1;
float Pva= Vpva*Ipva;

void setup()
{
  pinMode(13, OUTPUT);
}

void loop()
{ 
  digitalWrite(13, HIGH);
  
  Vpv=  (analogRead(analogVpvIn)*5.0*42.0)/1023.0;
  voltage_raw =   (5.0 / 1023.0)* analogRead(analogIpvPin);// Read the voltage from sensor
  voltage =  voltage_raw - QOV + 0.012 ;// 0.000 is a value to make voltage zero when there is no current
  Ipv = voltage / sensitivity;
  Pv= Ipv * Vpv;

  dv=Vpv-Vpva;
  di=Ipv-Ipva;
  dp=Pv-Pva;
  if (dp=0){
    D=D;
    }
  else{
    if(dp>0){
      if(dv<0){
        D=D+0.0001;
      }else{
        D=D-0.0001;
       }
    }else{
      if(dv<0){
        D=D-0.0001;}
      else {
      D=D+0.0001;
      }
      }
      }
  Pva=Pv;
  Vpva=Vpv;
  Ipva=Ipv;
  
  delayMicroseconds((0.54+D)*T);
  digitalWrite(13, LOW);
  delayMicroseconds((1-0.54-D)*T);
}

  //digitalWrite(13, HIGH);
  //delayMicroseconds(D*T); // Approximately 10% duty cycle @ 1KHz
  //digitalWrite(13, LOW);
  //delayMicroseconds((1-D)*T);
