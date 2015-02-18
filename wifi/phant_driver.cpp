/* 
 * Mantino Security
 * Brian Gravelle
 * Feb 2015
 * implements phant driver
*/


void initCC3000(){

  if ( wifi.init() ) {
    Serial.print("CC3000 initialization complete");
    Serial.print('\n'); 
  } else {
    Serial.print("Something went wrong during CC3000 init!");
    Serial.print('\n'); 
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
  Serial.print('\n');
  Serial.print('\n');
  
}

void connectToWiFi(){
  Serial.print("Connecting to SSID: ");
  Serial.print(ap_ssid);
  Serial.print('\n'); 
  if(!wifi.connect(ap_ssid, ap_security, ap_password, timeout)) {
    Serial.print("Error: Could not connect to AP");
    Serial.print('\n'); 
  }
}

void showConnectionInfo(){
  int i;
  
  if ( !wifi.getConnectionInfo(connection_info) ) {
    Serial.print("Error: Could not obtain connection details");
    Serial.print('\n'); 
  } else {
    Serial.print("IP Address: ");
    for (i = 0; i < IP_ADDR_LEN; i++) {
      Serial.print(connection_info.ip_address[i]);
      if ( i < IP_ADDR_LEN - 1 ) {
        Serial.print(".");
      }
    }
    Serial.print('\n'); 
  }  
}

void lookupServerIP(){
  int i;
 
  Serial.print("Looking up IP address of: ");
  Serial.print(server);
  Serial.print('\n'); 
  if ( !wifi.dnsLookup(server, &remote_ip) ) {
    Serial.print("Error: Could not lookup host by name");
    Serial.print('\n'); 
  } else {
    Serial.print("IP address found: ");
    for (i = 0; i < IP_ADDR_LEN; i++) {
      Serial.print(remote_ip[i], DEC);
      if ( i < IP_ADDR_LEN - 1 ) {
        Serial.print(".");
      }
    }
    Serial.print('\n');
  }
}

void setDisarmPost(){
  char string[] = "armed=F&alert=F";
  int j = 0;
  while(string[j] != '\0') {
     postString[j] = string[j];
     j++;
  }

  postString[j] = '\0';
}

void setArmPost(){
  char string[] = "armed=T&alert=F"; 
    int j = 0;
  while(string[j] != '\0') {
     postString[j] = string[j];
     j++;
  }

  postString[j] = '\0';
}

void setAlertPost(){
  char string[] = "armed=T&alert=T";
    int j = 0;
  while(string[j] != '\0') {
     postString[j] = string[j];
     j++;
  }

  postString[j] = '\0';
}


void updateServer(){  

  boolean connection = phant.connect();
  //delay(100);
  //if(connection) {
  //  Serial.print("Clearing data on ");
  //  Serial.print(server);
  //  Serial.print('\n');  
  //  phant.makeEmpty();
  //} else {
  //  Serial.print('\n');
  //  Serial.print("Failed to connect to ");
  //  Serial.print(server); 
  //  Serial.print('\n');   
  //}
  //delay(100);
  //
  //connection = phant.connect();
  delay(100);
  if(connection) { 
    Serial.print("Posting to ");
    Serial.print(server);
    Serial.print('\n'); 
    phant.post(postString);
  } else {
    Serial.print('\n');
    Serial.print("Failed to connect to ");
    Serial.print(server); 
    Serial.print('\n');   
  }
  
  delay(waitTime);
  
} //end updateServer

void checkServer(){ 
  char c;
  int i = 0;
  int nl_cnt = 0;
  
  if(phant.connect()) {
    phant.get();
    Serial.print("Getting data from ");
    Serial.print(server);
    Serial.print('\n');
    Serial.print('\n'); 
    c = phant.recieve();
    delay(100);
    
    while (c != '\0') {
	
      if ( (nl_cnt == 15) && (i < 62) ) {
         phantReply[i] = c; 
         i++;
      } else {
		if (c == '\n') 
         nl_cnt++;
      }  
      
	  //Serial.print(c); useful for debug
      c = phant.recieve();
    }
	    
    Serial.print("Phant data: ");
    Serial.print(phantReply); 
    Serial.print("\n"); 
   
  } else {
    Serial.print('\n');
    Serial.print("Failed to connect to ");
    Serial.print(server); 
    Serial.print('\n');   
  }
  
}

void syncArmToServer(){
    if( phantReply[2] == 'F') 
		armed = false;
	else 
		armed = true;
}

void syncAlertToServer(){
	if( phantReply[0] == 'T') 
		alarmed = true;
	else  
		alarmed = false;
}


