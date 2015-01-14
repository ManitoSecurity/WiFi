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
  * fix posting issue
  * find useful way to get info to app
  * make code pretty
  * incorporate BT

  **Known Problems**
  * difficultly posting (appears to send message but TS doesn't get it)
  * trouble with WEP security- might have to send key as hex (see wlan.h in WiFi library's utility)

  **Versions**

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
**WebClient_ex**
 * from Sparkfun
 * example connects to AP and sends GET to a website


