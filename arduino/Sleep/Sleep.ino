

/*
 Warduino - Sleep
 Example of sleeping and saving power
 
 This example code is in the public domain.
 
 Author: Bc. Josef Jebavý
 web: http://www.xeres.cz
 about project: http://www.multi.xeres.cz/programovani/wireless-arduino-low-power-consumption
 
 
 */



#include <avr/sleep.h>
#include <avr/wdt.h>
#include <SPI.h>
#include <RH_RF22.h>

// Singleton instance of the radio driver
RH_RF22 rf22;
#define LED 3

// watchdog interrupt
ISR(WDT_vect) 
{
  wdt_disable();  // disable watchdog
}

void myWatchdogEnable(const byte interval) 
{  

  // turn off brown-out enable in software
  MCUCR = bit (BODS) | bit (BODSE);
  MCUCR = bit (BODS); 

  int previousADCSRA = ADCSRA;    
  ADCSRA &= ~(1<<ADEN); //Disable ADC
  ACSR = (1<<ACD); //Disable the analog comparator
  DIDR0 = 0x3F; //Disable digital input buffers on all ADC0-ADC5 pins
  DIDR1 = (1<<AIN1D)|(1<<AIN0D); //Disable digital input buffer on AIN1/0


  //toto nejde zkompilovat pro atmega8
  MCUSR = 0;                          // reset various flags
  WDTCSR |= 0b00011000;               // see docs, set WDCE, WDE
  WDTCSR =  0b01000000 | interval;    // set WDIE, and appropriate delay

  wdt_reset();
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);  
  sleep_mode();            // now goes to Sleep and waits for the interrupt

  //zapnuti ADC
  ADCSRA = previousADCSRA;
} 

void setup()
{


  pinMode (LED, OUTPUT);

  PRR = bit(PRTIM1);                           // only keep timer 0 going
  // ADCSRA &= ~ bit(ADEN); 
  // bitSet(PRR, PRADC); 
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
  myWatchdogEnable (0b100001);  
  // sleep bit patterns:
  //  1 second:  0b000110
  //  2 seconds: 0b000111
  //  4 seconds: 0b100000
  //  8 seconds: 0b100001

}  





