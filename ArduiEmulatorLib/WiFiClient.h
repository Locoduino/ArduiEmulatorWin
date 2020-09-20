/*
  Client.h - Base class that provides Client
  Copyright (c) 2011 Adrian McEwen.  All right reserved.

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

#ifndef _WIFICLIENT_H_
#define _WIFICLIENT_H_


#include "Arduino.h"
#include "Client.h"
#include "Print.h"
#include <memory>

class WiFiClientSocketHandle;
class WiFiClientRxBuffer;

class ESPLwIPClient : public Client
{
public:
        virtual int connect(IPAddress ip, uint16_t port, int32_t timeout) = 0;
        virtual int connect(const char *host, uint16_t port, int32_t timeout) = 0;
        virtual int setTimeout(uint32_t seconds) = 0;
};

class WiFiClient : public ESPLwIPClient
{
protected:
    std::shared_ptr<WiFiClientSocketHandle> clientSocketHandle;
    std::shared_ptr<WiFiClientRxBuffer> _rxBuffer;
    bool _connected;

public:
    WiFiClient *next;
    WiFiClient(){}
    WiFiClient(int fd){}
    ~WiFiClient(){}
    int connect(IPAddress ip, uint16_t port){ return 0; }
    int connect(IPAddress ip, uint16_t port, int32_t timeout){return 0; }
    int connect(const char *host, uint16_t port){return 0; }
    int connect(const char *host, uint16_t port, int32_t timeout){return 0; }
    size_t write(uint8_t data){return 0; }
    size_t write(const uint8_t *buf, size_t size){return 0; }
    size_t write_P(PGM_P buf, size_t size){return 0; }
    //size_t write(Stream &stream){return 0; }
    int available(){return 0; }
    int read(){return 0; }
    int read(uint8_t *buf, size_t size){return 0; }
    String readString() { return String(); }
    int peek(){return 0; }
    void flush(){}
    void stop(){}
    uint8_t connected(){return 0; }

    operator bool()
    {
        return connected();
    }
    const WiFiClient & operator=(const WiFiClient &other) { return other;}
    bool operator==(const bool value)
    {
        return bool() == value;
    }
    bool operator!=(const bool value)
    {
        return bool() != value;
    }
    bool operator==(const WiFiClient&) { return false;}
    bool operator!=(const WiFiClient& rhs)
    {
        return !this->operator==(rhs);
    };

    int fd() const {return 0; }

    int setSocketOption(int option, char* value, size_t len){return 0; }
    int setOption(int option, int *value){return 0; }
    int getOption(int option, int *value){return 0; }
    int setTimeout(uint32_t seconds){return 0; }
    int setNoDelay(bool nodelay){return 0; }
    bool getNoDelay(){return false; }

    IPAddress remoteIP() const{return INADDR_NONE; }
    IPAddress remoteIP(int fd) const{return INADDR_NONE; }
    uint16_t remotePort() const{return 0; }
    uint16_t remotePort(int fd) const{return 0; }
    IPAddress localIP() const{return INADDR_NONE; }
    IPAddress localIP(int fd) const{return INADDR_NONE; }
    uint16_t localPort() const{return 0; }
    uint16_t localPort(int fd) const{return 0; }

    //friend class WiFiServer;
    using Print::write;
};

#endif /* _WIFICLIENT_H_ */
