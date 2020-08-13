#INCLUDE <16f887.h>

#device adc=10
#USE DELAY(CLOCK=4000000)
#FUSES XT,NOPROTECT,NOWDT,NOBROWNOUT,NOPUT,NOLVP
#INCLUDE <LCD.C>

#BYTE PORTA= 5
#BYTE PORTD= 8

#define SW PORTA,1
#define LED PORTB,0

#BYTE PORTB= 6

long Vpvin;     //Variable almacena los bits
float Vpv;     //Almacena la temperatura

float Ipvin ;        //variables de lectura nueva
float Ipv;
float Pv;
float dv;
float dp;
float di;

float voltage=0;
float voltage_raw=0;
float VCC= 5;// Voltaje de alimentacion del sensor de corriente
float  sensitivity =0.100;// sensibilidad del ACS712ELCTR-20A-T
float QOV =   0.5 * VCC;// set quiescent Output voltage of 0.5V

void main()
{
  
   SET_TRIS_B(0B11111110);
   set_tris_a(0b00000011);          //Pongo el RA0 como entrada
   set_tris_d(0);                   //Pongo el PuertoD como Salida
   setup_adc_ports(all_analog);     //Pongo todo el puerto a analogo
   setup_adc(adc_clock_internal);   //Selecciono reloj interno para conversion
   //lcd_init();                      //Inicializo el LCD
   //lcd_putc("\f");                  //Borro el LCD
   
   while(1)
   { BIT_SET(LED);
   
       set_adc_channel(0);          //Selecciono el canal 0 (RA0)
       Vpvin=read_adc();             //Guarde el dato del LM en tempe
           
       Vpv=(Vpvin*5.0);              //Conversion de bits a temperatura
       BIT_CLEAR(lED);
      // lcd_gotoxy(1,1);             //Ubiquese en la posicion 1,1
      // lcd_putc("V=");
       //lcd_gotoxy(3,1);             //Ubiquese en la posicion 2,2
      // printf(lcd_putc,"%f",Vpv);  //Muestra el valor numerico de la conversionconversion
       set_adc_channel(1);          //Selecciono el canal 0 (RA0)
       Ipvin=read_adc();             //Guarde el dato del LM en tempe
       voltage_raw =   (5.0 / 1023.0)*Ipvin;// Read the voltage from sensor
       voltage =  voltage_raw - QOV + 0.012 ;// 0.000 is a value to make voltage zero when there is no current
       Ipv = voltage / sensitivity;

       
      // lcd_gotoxy(1,2);             //Ubiquese en la posicion 1,1
      // lcd_putc("I=");
      // lcd_gotoxy(3,2);             //Ubiquese en la posicion 2,2
      // printf(lcd_putc,"%f",Ipv);  //Muestra el valor numerico de la conversionconversion
   }
}