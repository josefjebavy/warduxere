/*
  Warduino - Blink

  Turns on an LED on for one second, then off for one second, repeatedly.

  This example code is in the public domain.

  Author: Bc. Josef Jebavý
  web: http://www.xeres.cz
  about project: http://multi.xeres.cz/programovani/wireless-arduino-low-power-consumption

  
 */
#define PINLED 3

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);

  Serial.println("---- start ----");
      
  // initialize digital pin 3 as an output.
  pinMode(PINLED, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(PINLED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(PINLED, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);              // wait for a second
}
