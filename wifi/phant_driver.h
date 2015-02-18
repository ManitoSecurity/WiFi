/* phant_driver.h 
 * Mantino Security
 * Brian Gravelle
 * Feb 2015
 * implements phant driver
*/

/*
#include <SPI.h>
#include <SFE_CC3000.h>
#include <SFE_CC3000_Client.h>
#include <myPhant.h>
*/

#ifndef _PHANT_DRIVER_h
#define _PHANT_DRIVER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

// Pins
#define CC3000_INT      2   // Needs to be an interrupt pin (D2/D3)
#define CC3000_EN       7   // Can be any digital pin
#define CC3000_CS       10  // Preferred is pin 10 on Uno
#define IRPin           8
//#define IRPin           3 
#define IRDummy         6 

// Connection info data lengths
#define IP_ADDR_LEN     4   // Length of IP address in bytes

// Constants
unsigned int ap_security = WLAN_SEC_WEP; // Security of network
unsigned int timeout = 60000;             // Milliseconds

char server[] = "data.sparkfun.com";      // sparkfun data
char pub_key[] = "5JZO9K83dRU0KlA39EGZ";  // public key
char pri_key[] = "7BMDzNyXeAf0Kl25JoW1";  // private key
int waitTime= 30000;                      // limit update interval

// Global Variables
char ap_ssid[33];     // SSID of network
char ap_password[33]; // Password of network
IPAddress remote_ip;
ConnectionInfo connection_info;
int digiIRout;        // reading from IR
boolean armed, alarmed, state_change;
char postString[33];
char phantReply[64];

SFE_CC3000 wifi(CC3000_INT, CC3000_EN, CC3000_CS);
Phant phant(server, pub_key, pri_key, wifi);


void initCC3000();

void getWiFiInfo();

void connectToWiFi();

void showConnectionInfo();

void lookupServerIP();

void setDisarmPost();

void setArmPost();

void setAlertPost();

void updateServer();

void checkServer();

void syncArmToServer();

void syncAlertToServer();



#endif

