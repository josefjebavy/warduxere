/*
 Warduxere - Wireless client
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
  if (!rf22.init())
    Serial.println("init failed");
  // Defaults after init are 434.0MHz, 0.05MHz AFC pull-in, modulation FSK_Rb2_4Fd36
}

void loop()
{
  Serial.println("Sending to rf22_server");
  // Send a message to rf22_server
  uint8_t data[] = "Hello World!";
  rf22.send(data, sizeof(data));
  
  rf22.waitPacketSent();
  // Now wait for a reply
  uint8_t buf[RH_RF22_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if (rf22.waitAvailableTimeout(500))
  { 
    // Should be a reply message for us now   
    if (rf22.recv(buf, &len))
    {
      Serial.print("got reply: ");
      Serial.println((char*)buf);
    }
    else
    {
      Serial.println("recv failed");
    }
  }
  else
  {
    Serial.println("No reply, is rf22_server running?");
  }
  delay(400);
}

