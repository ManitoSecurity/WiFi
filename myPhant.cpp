/**
 * myPhant.cpp
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

#include "Arduino.h"
#include "myPhant.h"
#include <string.h>

Phant::Phant(string host, string publicKey, string privateKey) {
  _host = host;
  _pub = publicKey;
  _prv = privateKey;
  _params = "";
}

void Phant::add(string field, string data) {

  _params += "&" + field + "=" + data;

}

void Phant::add(string field, char data) {

  _params += "&" + field + "=" + std::to_string(data);

}

void Phant::add(string field, int data) {

  _params += "&" + field + "=" + std::to_string(data);

}

void Phant::add(string field, byte data) {

  _params += "&" + field + "=" + std::to_string(data);

}

void Phant::add(string field, long data) {

  _params += "&" + field + "=" + std::to_string(data);

}

void Phant::add(string field, unsigned int data) {

  _params += "&" + field + "=" + std::to_string(data);

}

void Phant::add(string field, unsigned long data) {

  _params += "&" + field + "=" + std::to_string(data);

}

void Phant::add(string field, double data) {

  char tmp[30];

  dtostrf(data, 1, 4, tmp);

  _params += "&" + field + "=" + std::to_string(tmp);

}

void Phant::add(string field, float data) {

  char tmp[30];

  dtostrf(data, 1, 4, tmp);

  _params += "&" + field + "=" + std::to_string(tmp);

}

string Phant::queryString() {
  return std::to_string(_params);
}

string Phant::url() {

  string result = "http://" + _host + "/input/" + _pub + ".txt";
  result += "?private_key=" + _prv + _params;

  _params = "";

  return result;

}

string Phant::get() {

  string result = "GET /output/" + _pub + ".csv HTTP/1.1\n";
  result += "Host: " + _host + "\n";
  result += "Connection: close\n";

  return result;

}

string Phant::post() {

  string params = _params.substring(1);

  string result = "POST /input/" + _pub + ".txt HTTP/1.1\n";
  result += "Host: " + _host + "\n";
  result += "Phant-Private-Key: " + _prv + "\n";
  result += "Connection: close\n";
  result += "Content-Type: application/x-www-form-urlencoded\n";
  result += "Content-Length: " + std::to_string(params.length()) + "\n\n";
  result += params;

  _params = "";

  return result;

}

string Phant::clear() {

  string result = "DELETE /input/" + _pub + ".txt HTTP/1.1\n";
  result += "Host: " + _host + "\n";
  result += "Phant-Private-Key: " + _prv + "\n";
  result += "Connection: close\n";

  return result;

}
