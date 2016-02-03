/*
 Warduxere - Wireless server
 Example of wireles comunication.
 Tested on Warduxere: Atmega328 and SI4432
 
 This example code is in the public domain.
 
 about Warduxere: http://multi.xeres.cz/programovani/wireless-arduino-low-power-consumption
 
 
 */



#include <SPI.h>
#include <RH_RF22.h>

// Singleton instance of the radio driver
RH_RF22 rf22;

void setup() 
{
  Serial.begin(9600);
  if (!rf22.init()){
    Serial.println("init failed");  
    Serial.flush();
  // Defaults after init are 434.0MHz, 0.05MHz AFC pull-in, modulation FSK_Rb2_4Fd36
  }else{
    Serial.println("init ok");  
    Serial.flush();
  }
}
void loop()
{
  if (rf22.available())
  {
    // Should be a message for us now   
    uint8_t buf[RH_RF22_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf22.recv(buf, &len))
    {
//      RF22::printBuffer("request: ", buf, len);
      Serial.print("got request: ");
      Serial.println((char*)buf);
//      Serial.print("RSSI: ");
//      Serial.println(rf22.lastRssi(), DEC);
      
      // Send a reply
      uint8_t data[] = "And hello back to you";
      rf22.send(data, sizeof(data));
      rf22.waitPacketSent();
      Serial.println("Sent a reply");
    }
    else
    {
      Serial.println("recv failed");
    }
  }
}

