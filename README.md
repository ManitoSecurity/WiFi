================================================================
Manito Security WiFi
================================================================

Arduino sketches to prototype WiFi communication
CC3000 info here: https://www.sparkfun.com/products/12072

----------------------------------------------------------------------------

**wifi** 
----------------------------------------------------------------------------
  * prototype communication arduino over wifi
  * currently posts to thing speak (user bgravelle pass Manito@2)

  **TO DO**
  * reinitiate connection to TS for each post
  * make code pretty
  * incorporate BT

  **Known Problems**
  * difficultly maintaining connection to TS
  * trouble with WEP security

  **Versions**

  *wifi_v1_3*
   * not working
   * gets input from IR and attempt to appropriately post
   * only posts once; cannot maintain connection

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
**WebClient_ex**
 * from Sparkfun
 * example connects to AP and sends GET to a website


