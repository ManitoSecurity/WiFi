/**
 * myPhant.h
 *
 * Author: Brian Gravelle
 * Based on Phant.h by Todd Treece <todd@sparkfun.com>
 *
 */
 

#include "Arduino.h"
#include "Phant.h"

Phant::Phant(char* host, char* publicKey, char* privateKey, SFE_CC3000_Client* client) {
  _host = host;
  _pub = publicKey;
  _prv = privateKey;
  _params[0] = '\0';
  _param_length = 0;
  _client = client
}

bool connect(){
  return !(_client->connect(_host, 80));
}

void Phant::add(char* field, char* data) {

  int j = 0;

  _params[_param_length] = '&';
  _param_length++;
  while(field[j] != '\0') {
     _params[_param_length] = field[j];
     j++; _param_length++;
  }
  _params[_param_length] = '=';

  _param_length++;
  while(field[i] != '\0') {
     _params[_param_length] = data[j];
     j++; _param_length++;
  }

}

char* Phant::queryString() {
  return _params;
}

char* Phant::url() {

  String result = "http://" + _host + "/input/" + _pub + ".txt";
  result += "?private_key=" + _prv + _params;

  _params = "";

  return result;

}

void Phant::get() {

  _client->print("GET /output/"); _client->print(_pub); 
     _client->println(".csv HTTP/1.1");
  _client->print("Host: "); _client->println(_host);
  _client->println("Connection: close");

}

void Phant::post() {

  //skip first &
  char* params = &_params[1];

  _client->print("POST /input/"); _client->print(_pub); 
      _client->println(".txt HTTP/1.1");
  _client->print("Host: "); _client->println(_host);
  _client->print("Phant-Private-Key: "); _client->println(_prv);
  _client->println("Connection: close");
  _client->println("Content-Type: application/x-www-form-urlencoded");
  _client->print("Content-Length: "); _client->print(_params_length);
  _client->print("\n\n");
  _client->print(params);

  _params = "";

}

void Phant::clear() {

  int _param_length;
  _client->print("DELETE /input/"); _client->print(_pub); 
     _client->println(".txt HTTP/1.1");
  _client->print("Host: "); _client->println(_host);
  _client->print("Phant-Private-Key: "); _client->println(_prv);
  _client->println("Connection: close");

}