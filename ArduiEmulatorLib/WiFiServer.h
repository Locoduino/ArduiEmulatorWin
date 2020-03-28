/*
  Server.h - Server class for Raspberry Pi
  Copyright (c) 2016 Hristo Gochkov  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#ifndef _WIFISERVER_H_
#define _WIFISERVER_H_

#include "Arduino.h"
#include "Server.h"
#include "WiFiClient.h"

class WiFiServer : public Server {
public:
    void listenOnLocalhost(){}

    WiFiServer(uint16_t port=80, uint8_t max_clients=4){}
    ~WiFiServer(){ end();}
    WiFiClient available() {return NULL;}
    WiFiClient accept(){return available();}
    void begin() {}
    void begin(uint16_t port){}
    void setNoDelay(bool nodelay){}
    bool getNoDelay(){return false;}
    bool hasClient(){return false;}
    size_t write(const uint8_t *data, size_t len){return 0;}
    size_t write(uint8_t data){
      return write(&data, 1);
    }
    using Print::write;

    void end(){}
    void close(){}
    void stop(){}
    operator bool(){return false;}
    int setTimeout(uint32_t seconds){return 0;}
    void stopAll(){}
};

#endif /* _WIFISERVER_H_ */
