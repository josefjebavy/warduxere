

/*
 Warduxere - Sleep
 Example of sleeping and saving power
 
 This example code is in the public domain.
 
 Author: Bc. Josef Jebavý
 web: http://www.xeres.cz
 about project: http://www.multi.xeres.cz/wireless-arduino-low-power-consumption
 
 
 */




#include <SPI.h>
#include <RH_RF22.h>
#include "LowPower.h"

// Singleton instance of the radio driver
RH_RF22 rf22;
#define LED 3





void setup()
{


  pinMode (LED, OUTPUT);

  rf22.init();
}  


void loop()
{


  // awake
  digitalWrite (LED, HIGH);  
  delay (4000);

  //not sleeping not lihgt
  digitalWrite (LED, LOW); 
  delay (4000); 


   //blink before sleep
  digitalWrite (LED, HIGH);  
  delay (200);
  digitalWrite (LED, LOW); 

  //sleep wireless module
  rf22.sleep();
  // sleep 8 seconds
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
 //   LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF,                 SPI_OFF, USART0_OFF, TWI_OFF);
//  myWatchdogEnable (0b100001);  
  // sleep bit patterns:
  //  1 second:  0b000110
  //  2 seconds: 0b000111
  //  4 seconds: 0b100000
  //  8 seconds: 0b100001

}  





