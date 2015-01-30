================================================================
Manito Security WiFi
================================================================

Arduino sketches to prototype WiFi communication
CC3000 info here: https://www.sparkfun.com/products/12072

----------------------------------------------------------------------------

**wifi** 
----------------------------------------------------------------------------
  * prototype communication arduino over wifi
  * will post to https://data.sparkfun.com/streams/5JZO9K83dRU0KlA39EGZ

  **TO DO**
  * resolve phant.add() issues
  * posting: establish TCP connection, send HTTP command from Phant object
  * make code pretty
  * incorporate BT

  **Known Problems**
  * trouble with WEP security- might have to send key as hex (see wlan.h in WiFi library's utility)
  * currently cannot vary posted message

  **Versions**

  *wifi_v1_5*
   * almost working; can post hard coded message to server
   * problem occurs in phant.add
   * making it work with data.sparkfun.com
   * uses myPhant class (phant is sparkfun's name for their server system)

  *wifi_v1_4*
   * not working
   * switch from thingspeak to data.sparkfun.com feed
   * gets input from IR and attempt to appropriately post

  *wifi_v1_3*
   * not working
   * gets input from IR and attempt to appropriately post
   * claims to post but TS doesn't agree

  *wifi_v1_2*
   * working (not useful but working)
   * successful posting to thingspeak
   * just switches between 2 values
   * fun fact: I think there is a minimum delay between posts

  *wifi_v1_1*
   * added thing speak posting
   * pings api.thingspeak.com first to check WiFi issues

  *wifi_v1*
   * initial prototype
   * sends HTTP GET to example.com

----------------------------------------------------------------------------

**other stuff**
----------------------------------------------------------------------------
**myPhant.cpp and .h**
 * library to produce http commands to update data.sparkfun.com feed
 * the original library provided by Sparkfun is incompatible with the WiFi chip
 * this version is designed to connect to the server and send the messages
 * WiFi actually includes the versions in sketchbook/libraries, so update those

**WebClient_ex**
 * from Sparkfun
 * example connects to AP and sends GET to a website


