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
  * make it loop
  * incorporate BT and IR

  **Known Problems**
  * only posts once
  * trouble with WEP security

  **Versions**

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


