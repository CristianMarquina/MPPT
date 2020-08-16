#INCLUDE <16f887.h>
#device adc=10
#USE DELAY(CLOCK=4000000)
#FUSES XT,NOPROTECT,NOWDT,NOBROWNOUT,NOPUT,NOLVP
#include <lcd.c>

#BYTE PORTA= 5
#BYTE PORTD= 8

long Vpvin;     //Lectura de la entrada para el voltaje de salida del arreglo de paneles
float Vpv;     //Almacena el voltaje de salida del arreglo de paneles
long Ipvin = 0;     //Lectura de la entrada para la corriente de salida del arreglo de paneles
float Ipv= 0; //Almacena la corriente de salida del arreglo de paneles
float Pvp= 0; //Almacena La potencia de salida del arreglo de paneles

const float VCC=5;// Voltaje de alimentacion del sensor de corriente
float  sensitivity =0.100;// sensibilidad del ACS712ELCTR-20A-T
const float QOV =   0.5 * VCC;
float voltage;//Voltaje que da la lectura de corriente
float voltage_raw;

long Vlin;     //Lectura de la entrada para el voltaje de salida del arreglo de paneles
float Vl;     //Almacena el voltaje de salida del arreglo de paneles
long Ilin = 0;     //Lectura de la entrada para la corriente de salida del arreglo de paneles
float Il= 0; //Almacena la corriente de salida del arreglo de paneles
float Pl= 0; //Almacena La potencia de salida del arreglo de paneles

float voltagel;//Voltaje que da la lectura de corriente
float voltage_rawl;


void main()
{
   set_tris_a(0b00001111);          //Pongo el RA0 como entrada
   set_tris_d(0);                   //Pongo el PuertoD como Salida
   setup_adc_ports(all_analog);     //Pongo todo el puerto a analogo
   setup_adc(adc_clock_internal);   //Selecciono reloj interno para conversion
   lcd_init();                      //Inicializo el LCD
   lcd_putc("\f");                  //Borro el LCD
   
   while(1)
   {
       set_adc_channel(0);          //Selecciono el canal 0 (RA0)
       Vpvin=read_adc();             //Guarde el dato de el voltaje de salida de los paneles
       Vpv=  (Vpvin*5.0*42.0)/1023.0;
       
       lcd_gotoxy(1,1);             //Ubiquese en la posicion 2,2
       printf(lcd_putc,"Vpv=%f",Vpv);  //Muestra el valor del voltaje de salida de arreglo de los paneles
       
       set_adc_channel(1);          //Selecciono el canal 1 (RA1)
       Ipvin=read_adc(); 
       voltage_raw =   (5.0 / 1023.0)* Ipvin;// Lee voltaje del sensor de corriente
       voltage =  voltage_raw - QOV + 0.012 ;
       Ipv = voltage / sensitivity;
       lcd_gotoxy(12,1);             //Ubiquese en la posicion 13,1
       printf(lcd_putc,"Ipv=%f",Ipv);  //Muestra el valor de La corriente de salida de arreglo de los paneles
       
       Pvp=Ipv*Vpv;
       lcd_gotoxy(6,2);             //Ubiquese en la posicion 7,2
       printf(lcd_putc,"Pvp=%f",Pvp);  //Muestra el valor de La potencia de salida de arreglo de los paneles
       
       
       set_adc_channel(2);          //Selecciono el canal 0 (RA2)
       Vlin=read_adc();             //Guarde el dato de el voltaje de la carga
       Vl=  (Vlin*5.0*100.0)/1023.0;
       
       lcd_gotoxy(21,1);             //Ubiquese en la posicion 3,1
       printf(lcd_putc,"Vl=%f",Vl);  //Muestra el valor del voltaje de la carga
       
       set_adc_channel(3);          //Selecciono el canal 1 (RA3)
       Ilin=read_adc(); 
       voltage_rawl =   (5.0 / 1023.0)* Ilin;// Lee voltaje del sensor de corriente para la carga
       voltagel =  voltage_rawl - QOV + 0.012 ;
       Il = voltagel / sensitivity;
       lcd_gotoxy(32,1);             //Ubiquese en la posicion 12,3
       printf(lcd_putc,"Il=%f",Il);  //Muestra el valor de La corriente de la carga
       
       Pl=Il*Vl;
       lcd_gotoxy(28,2);             //Ubiquese en la posicion 7,4
       printf(lcd_putc,"Pl=%f",Pl);  //Muestra el valor de La potencia de salida de arreglo de los paneles
       
   }
}
