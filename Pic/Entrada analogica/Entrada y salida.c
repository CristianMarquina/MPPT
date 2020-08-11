
#INCLUDE <16f887.h>  
#USE   delay (clock=4000000)        //incluimos el codigo del pic
#FUSES xt,protect,nowdt,nobrownout,put,nolvp
#define SW PORTA,1
#define LED PORTB,0
#BYTE PORTA= 5
#BYTE PORTB= 6
             
void main (){
      SET_TRIS_A(0B10);
      SET_TRIS_B(0B11111110);
      while (true){
         IF(BIT_TEST(SW)){ //
            BIT_SET(LED);
         }
         ELSE{
         BIT_CLEAR(lED);
         }
      }
}
