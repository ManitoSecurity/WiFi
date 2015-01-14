/****************************************************************
wifi_v1_3.ino
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
String.h

Development environment specifics:
Written in Arduino 1.0.5
Tested with Arduino UNO R3

pub  5JZO9K83dRU0KlA39EGZ
pri  7BMDzNyXeAf0Kl25JoW1
url  https://data.sparkfun.com/streams/5JZO9K83dRU0KlA39EGZ

****************************************************************/

#include <SPI.h>
#include <SFE_CC3000.h>
#include <SFE_CC3000_Client.h>
#include <string.h>
#include <Phant.h>

// Pins
#define CC3000_INT      2   // Needs to be an interrupt pin (D2/D3)
#define CC3000_EN       7   // Can be any digital pin
#define CC3000_CS       10  // Preferred is pin 10 on Uno

#define IRPin           8 

// Connection info data lengths
#define IP_ADDR_LEN     4   // Length of IP address in bytes

// Constants
unsigned int ap_security = WLAN_SEC_WPA2; // Security of network
unsigned int timeout = 60000;             // Milliseconds
char server[] = "data.sparkfun.com";      // sparkfun data
String pri_key = "7BMDzNyXeAf0Kl25JoW1";  // private key
String pub_key = "5JZO9K83dRU0KlA39EGZ";  // public key
int waitTime= 30000;                      // limit update interval

Phant phant(server, pub_key, pri_key);

// Global Variables
SFE_CC3000 wifi = SFE_CC3000(CC3000_INT, CC3000_EN, CC3000_CS);
SFE_CC3000_Client client = SFE_CC3000_Client(wifi);

char ap_ssid[33];     // SSID of network
char ap_password[33]; // Password of network
String postString;    // string to post to thing speak
int digiIRout;        // reading from IR
int curr_alarm;
int prev_alarm;
IPAddress remote_ip;
ConnectionInfo connection_info;


void initCC3000(){
 
  if ( wifi.init() ) {
    Serial.println("CC3000 initialization complete");
  } else {
    Serial.println("Something went wrong during CC3000 init!");
  }
  
}

void getWiFiInfo(){
  
  Serial.setTimeout(10000);
  Serial.print("Enter SSID: ");
  Serial.readBytesUntil('\n',ap_ssid,33);
  delay(1000);
  Serial.print("\nEnter Password: ");
  Serial.readBytesUntil('\n',ap_password,33);
  delay(1000);
  Serial.println("\n");
  
}

void connectToWiFi(){
  Serial.print("Connecting to SSID: ");
  Serial.println(ap_ssid);
  if(!wifi.connect(ap_ssid, ap_security, ap_password, timeout)) {
    Serial.println("Error: Could not connect to AP");
  }
}

void showConnectionInfo(){
  int i;
  
  if ( !wifi.getConnectionInfo(connection_info) ) {
    Serial.println("Error: Could not obtain connection details");
  } else {
    Serial.print("IP Address: ");
    for (i = 0; i < IP_ADDR_LEN; i++) {
      Serial.print(connection_info.ip_address[i]);
      if ( i < IP_ADDR_LEN - 1 ) {
        Serial.print(".");
      }
    }
    Serial.println();
  }  
}

void lookupServerIP(){
  int i;
 
  Serial.print("Looking up IP address of: ");
  Serial.println(server);
  if ( !wifi.dnsLookup(server, &remote_ip) ) {
    Serial.println("Error: Could not lookup host by name");
  } else {
    Serial.print("IP address found: ");
    for (i = 0; i < IP_ADDR_LEN; i++) {
      Serial.print(remote_ip[i], DEC);
      if ( i < IP_ADDR_LEN - 1 ) {
        Serial.print(".");
      }
    }
    Serial.println();
  }
}

void setup() {
  
  // Initialize Serial port
  Serial.begin(115200);
  Serial.println();
  Serial.println("---------------------------");
  Serial.println("        Manito WiFi        ");
  Serial.println("---------------------------");
  
  pinMode(IRPin, INPUT);      
    
  initCC3000();  
  getWiFiInfo();  
  connectToWiFi();
  showConnectionInfo();
  lookupServerIP();
  
  curr_alarm = 1;
  prev_alarm = 0;

} //end setup

void setDisarmPost(){
  phant.add("armed",false);
  phant.add("alert",false); 
}

void setArmPost(){
  phant.add("armed",true);
}

void setAlertPost(){
  phant.add("alert",true);
}

void setShutUpPost(){
  phant.add("alert",true);
}

void updateServer(){  
  
  Serial.print("Posting to ");
  Serial.println(server);
  
  phant.post();
  
  delay(waitTime);
  
} //end updateServer

void loop() {
  
    digiIRout = digitalRead(IRPin);
    prev_alarm = curr_alarm;
    
    if(digiIRout == LOW) { 
      setAlertPost();
      curr_alarm = 2;
    } else {
      setShutUpPost();
      curr_alarm = 1;
    }
    
    if(curr_alarm != prev_alarm){
     updateServer();
    }
  
} // end loop
