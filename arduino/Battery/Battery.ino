/*
  Warduino - Battery
 
 Get battery status 
 This example code is in the public domain.
 
 Author: Bc. Josef Jebavý
 web: http://www.xeres.cz
 about project: http://multi.xeres.cz/programovani/wireless-arduino-low-power-consumption
 
 
 */

#define PINBAT A1
// the setup routine runs once when you press reset:
void setup() {

  Serial.begin(9600);

  pinMode(PINBAT, INPUT);


}

// the loop routine runs over and over again forever:
void loop() {


  //mereni baterie
  int sensorValue=analogRead(PINBAT);
  byte bat=0;

  // na LDO je ubitek napeti 0.178V takze pod 3.478V na baterii uz procesor a ADC bude napajen mene jak 3.3V
  // pro 3.3V arduino a delic 1:1 bude cislo odpovidat napeti na baterii:
  // 528 - 3.40V
  // 539 - 3.478V - hranice pro spravne napajeni
  // 550 - 3.544
  // 559 - 3.60V - hranice pro li-pol/ion baterii

  if (  sensorValue>558) {  
    bat=1;  
  }



  Serial.print("battery:");
  Serial.print(bat);
  Serial.print(";value:");
  Serial.print(sensorValue);
  Serial.print(";V:");
  double d =3.3/1024*sensorValue*2;
  Serial.print(d,4);
  Serial.println();

  delay(1000);  
}









