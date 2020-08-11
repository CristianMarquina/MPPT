#include <LiquidCrystal.h>
const float analogVpvIn = A0;  // Analog input pin that the potentiometer is attached to
const float analogIpvPin = A1; // Analog output pin that the LED is attached to
float D=0.17;
float d=0.17;
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

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  pinMode(13, OUTPUT);    // sets the digital pin 13 as output
  lcd.begin(16, 2);
  lcd.setCursor(0,0); // ubica cursor en columna 0, linea 0
  lcd.print("V=");
  lcd.setCursor(7,0);
  lcd.print("V");
  lcd.setCursor(9,0);
  lcd.print("I=");
  lcd.setCursor(15,0);
  lcd.print("A");\
  lcd.setCursor(0,1);
  lcd.print("P=");
  lcd.setCursor(8,1);
  lcd.print("W");
  lcd.setCursor(10,1);
  lcd.print("D=");
}

void loop() {
  digitalWrite(13, HIGH); // sets the digital pin 13 on
  Vpv=  (analogRead(analogVpvIn)*5.0*42.0)/1023.0;
  voltage_raw =   (5.0 / 1023.0)* analogRead(analogIpvPin);// Read the voltage from sensor
  voltage =  voltage_raw - QOV + 0.012 ;// 0.000 is a value to make voltage zero when there is no current
  Ipv = voltage / sensitivity;
  Pv= Ipv * Vpv;

  dv=Vpv-Vpva;
  di=Ipv-Ipva;
  dp=Pv-Pva;
   if (dp>0){
    if (dv>0){
      if(di>0){
        D=D+0.01;
      }
      else{
       D=D-0.01;
      }
    }
    else{
      D+0.01;
    }
  }

  else if(dv>0){
    D=D+0.01;
    }
    else{
      D=D-0.01;
    }
  Pva=Pv;
  Vpva=Vpv;
  Ipva=Ipv;
  lcd.setCursor(2,0); // ubica cursor en columna 0, linea 0
  lcd.print(Vpv,1);
  lcd.setCursor(11,0); // ubica cursor en columna 0, linea 0
  lcd.print(Ipv,2);
  lcd.setCursor(2,1); // ubica cursor en columna 0, linea 0
  lcd.print(Pv,1);
  lcd.setCursor(12,1); // ubica cursor en columna 0, linea 0
  lcd.print(D,2);
  
  digitalWrite(13, LOW); // sets the digital pin 13 on
  
}
