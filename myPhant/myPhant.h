/**
 * myPhant.h
 *
 * Author: Brian Gravelle
 * Based on Phant.h by Todd Treece <todd@sparkfun.com>
 *
 */

#ifndef Phant_h
#define Phant_h

#include "Arduino.h"
#include <SPI.h>
#include <SFE_CC3000.h>
#include <SFE_CC3000_Client.h>

class Phant {

  public:
    Phant(char* host, char* publicKey, char* privateKey, SFE_CC3000_Client* client);
    bool connect();
    void add(String field, String data);
    char* queryString();
    char* url();
    void get();
    void post();
    void clear();

  private:
    char _pub[256];
    char _prv[256];
    char _host[256];
    char _params[256];
    SFE_CC3000_Client* _client

};

#endif
