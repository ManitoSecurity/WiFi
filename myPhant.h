/**
 * Phant.h
 *
 *             .-.._
 *       __  /`     '.
 *    .-'  `/   (   a \
 *   /      (    \,_   \
 *  /|       '---` |\ =|
 * ` \    /__.-/  /  | |
 *    |  / / \ \  \   \_\  jgs
 *    |__|_|  |_|__\
 *    never   forget.
 *
 * Author: Todd Treece <todd@sparkfun.com>
 *         minor adjustments by Brian Gravelle
 *
 * Copyright (c) 2014 SparkFun Electronics.
 * Licensed under the GPL v3 license.
 *
 */

#ifndef Phant_h
#define Phant_h

#include "Arduino.h"
#include <string.h>

class Phant {

  public:
    Phant(string host, string publicKey, string privateKey);
    void add(string field, string data);
   /* void add(string field, char data);
    void add(string field, int data);
    void add(string field, byte data);
    void add(string field, long data);
    void add(string field, unsigned int data);
    void add(string field, unsigned long data);
    void add(string field, float data);
    void add(string field, double data);  */
    string queryString();
    string url();
    string get();
    string post();
    string clear();

  private:
    string _pub;
    string _prv;
    string _host;
    string _params;

};

#endif
