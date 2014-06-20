// Developed by Clovis Fritzen in June 20th, 2014
// It tests both buttons and LEDS of the Freescale
// Freedom FRDM-K64F development board
// 
#include "mbed.h"

DigitalOut RedLed(LED1);
DigitalOut GreenLed(LED2);
DigitalOut BlueLed(LED3);
DigitalIn Switch1(PTC6); // SW2 (right side) of Freedom board
DigitalIn Switch2(PTA4); // SW3 (left side) of Freedom board


int main() {
    
  while(1){
       
     if (!Switch1){ // "!" means that the the switches are inverted logic
             RedLed= 0; // Turns Red Led on (Inverted logic)
             GreenLed= 1;
             BlueLed= 1;
             } else {
                 if (!Switch2){ // "!" means that the the switches are inverted logic
                     RedLed= 1;
                     GreenLed= 0; // Turns Green Led on (Inverted logic)
                     BlueLed= 1;
                     } else {
                         RedLed= 1;
                         GreenLed= 1;
                         BlueLed= 0; // Turns Blue Led on (Inverted logic)
                         }
                 }
             }
}