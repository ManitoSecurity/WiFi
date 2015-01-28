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
myPhant.h

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
#include <myPhant.h>

// Pins
#define CC3000_INT      2   // Needs to be an interrupt pin (D2/D3)
#define CC3000_EN       7   // Can be any digital pin
#define CC3000_CS       10  // Preferred is pin 10 on Uno
#define IRPin           8 

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
int curr_alarm;
int prev_alarm;

SFE_CC3000 wifi          = SFE_CC3000(CC3000_INT, CC3000_EN, CC3000_CS);
Phant phant              = Phant(server, pub_key, pri_key, wifi);


void initCC3000(){
  if ( wifi.init() ) {
    Serial.print("CC3000 initialization complete");
    Serial.print("\n"); 
  } else {
    Serial.print("Something went wrong during CC3000 init!");
    Serial.print("\n"); 
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
  Serial.print("\n\n"); 
  
}

void connectToWiFi(){
  Serial.print("Connecting to SSID: ");
  Serial.print(ap_ssid);
  Serial.print("\n"); 
  if(!wifi.connect(ap_ssid, ap_security, ap_password, timeout)) {
    Serial.print("Error: Could not connect to AP");
    Serial.print("\n"); 
  }
}

void showConnectionInfo(){
  int i;
  
  if ( !wifi.getConnectionInfo(connection_info) ) {
    Serial.print("Error: Could not obtain connection details");
    Serial.print("\n"); 
  } else {
    Serial.print("IP Address: ");
    for (i = 0; i < IP_ADDR_LEN; i++) {
      Serial.print(connection_info.ip_address[i]);
      if ( i < IP_ADDR_LEN - 1 ) {
        Serial.print(".");
      }
    }
    Serial.print("\n"); 
  }  
}

void lookupServerIP(){
  int i;
 
  Serial.print("Looking up IP address of: ");
  Serial.print(server);
  Serial.print("\n"); 
  if ( !wifi.dnsLookup(server, &remote_ip) ) {
    Serial.print("Error: Could not lookup host by name");
    Serial.print("\n"); 
  } else {
    Serial.print("IP address found: ");
    for (i = 0; i < IP_ADDR_LEN; i++) {
      Serial.print(remote_ip[i], DEC);
      if ( i < IP_ADDR_LEN - 1 ) {
        Serial.print(".");
      }
    }
    Serial.print("\n");
  }
}

void setDisarmPost(){
  phant.add("armed","F");
  phant.add("alert","F"); 
}

void setArmPost(){
  phant.add("armed","T"); //need both because we clear old data
  phant.add("alert","F"); 
}

void setAlertPost(){
  phant.add("armed","T");
  phant.add("alert","T");
}

void setShutUpPost(){
  phant.add("armed","T");
  phant.add("alert","F");
}

void updateServer(){  
  
  
  if(phant.connect()) {
    Serial.print("Posting to ");
    Serial.print(server);
    Serial.print("\n"); 
    //phant.clear();
    phant.post();
  } else {
    Serial.print("Failed to connect to ");
    Serial.print(server); 
    Serial.print("\n");   
  }
  
  delay(waitTime);
  
} //end updateServer

void checkServer(){
  phant.get();
}


void setup() {
  
  // Initialize Serial port
  Serial.begin(115200);
  Serial.print("\n"); 
  Serial.print("---------------------------\n");
  Serial.print("        Manito WiFi        \n");
  Serial.print("---------------------------\n");
  
  pinMode(IRPin, INPUT);

  initCC3000();  
  getWiFiInfo(); 
  connectToWiFi();
  showConnectionInfo();
  lookupServerIP();
  
  curr_alarm = 1;
  prev_alarm = 0;

  setAlertPost();
  updateServer();

  Serial.print("       Setup Complete      \n");
  Serial.print("---------------------------\n");
  
} //end setup


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
