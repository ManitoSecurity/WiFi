/****************************************************************
wifi.ino
Manito Security Solutions
Brian Gravelle
Jan 8, 2015
Prototype for WiFi communication from Arduino
many thanks to Shawn Hymel @ SparkFun Electronics for creating
  the CC3000 library
  https://github.com/sparkfun/SFE_CC3000_Library
The security mode is defined by one of the following:
WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA, WLAN_SEC_WPA2
Hardware Connections:
 
 Uno Pin    CC3000 Board    Function
 
 +5V        VCC or +5V      5V
 GND        GND             GND
 2          INT             Interrupt
 7          EN              WiFi Enable
 10         CS              SPI Chip Select
 11         MOSI            SPI MOSI
 12         MISO            SPI MISO
 13         SCK             SPI Clock
Resources:
Include SPI.h, SFE_CC3000.h, and SFE_CC3000_Client.h
(SFE_CC3000_Library_master)
myPhant.h

Development environment specifics:
Written in Arduino 1.0.5
Tested with Arduino UNO R3

pub  5JZO9K83dRU0KlA39EGZ
pri  7BMDzNyXeAf0Kl25JoW1
url  https://data.sparkfun.com/streams/5JZO9K83dRU0KlA39EGZ
****************************************************************/

#include "phant_driver.h"

#include <SPI.h>
#include <SFE_CC3000.h>
#include <SFE_CC3000_Client.h>
#include <myPhant.h>

void setup() {
  
  // Initialize Serial port
  Serial.begin(115200);
  Serial.print('\n'); 
  Serial.print("---------------------------\n");
  Serial.print("        Manito WiFi        \n");
  Serial.print("---------------------------\n");
  
  pinMode(IRPin, INPUT);
  pinMode(IRDummy, OUTPUT);
  digitalWrite(IRDummy, HIGH);

  initCC3000();  
  getWiFiInfo(); 
  connectToWiFi();
  showConnectionInfo();
  lookupServerIP();
   
  state_change = true;
  armed = true; alarmed = false;

  setArmPost();
  updateServer();
  checkServer();
  
  Serial.print("       Setup Complete      ");
  Serial.print('\n'); 
  Serial.print("---------------------------");
  Serial.print('\n'); 
  
} //end setup


void loop() {
    
	//delay(30000);
    digiIRout = digitalRead(IRPin);
    
	if ( armed ) {
		if(digiIRout == LOW) { 
		  setAlertPost();
		  state_change = !alarmed; //if not alarming you changed!
		  alarmed = true;
		} else {
		  setArmPost();
		  state_change = alarmed;
		  alarmed = false;
		}
	
	}

	if( state_change ) {
		
	   checkServer();
	   syncArmToServer();
	   delay(100);
       if( armed ) {
	      updateServer();
	   } else {
		   syncAlertToServer();
		   delay(100);
		   Serial.println("disarmed");
		   state_change = false;
	   }
	   
	    state_change = false;
	}
  
} // end loop
