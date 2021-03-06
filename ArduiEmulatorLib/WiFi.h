/*
 WiFi.h - esp32 Wifi support.
 Based on WiFi.h from Arduino WiFi shield library.
 Copyright (c) 2011-2014 Arduino.  All right reserved.
 Modified by Ivan Grokhotkov, December 2014

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

#ifndef WiFi_h
#define WiFi_h

#include <stdint.h>

#include "Print.h"
#include "IPAddress.h"
//#include "IPv6Address.h"

#include "WiFiType.h"
//#include "WiFiSTA.h"
#include "WiFiAP.h"
//#include "WiFiScan.h"
#include "WiFiGeneric.h"

#include "WiFiClient.h"
#include "WiFiServer.h"
#include "WiFiUdp.h"

class WiFiClass : public WiFiGenericClass, public WiFiAPClass//, public WiFiSTAClass, public WiFiScanClass
{
/*public:
    using WiFiGenericClass::channel;

    using WiFiSTAClass::SSID;
    using WiFiSTAClass::RSSI;
    using WiFiSTAClass::BSSID;
    using WiFiSTAClass::BSSIDstr;

    using WiFiScanClass::SSID;
    using WiFiScanClass::encryptionType;
    using WiFiScanClass::RSSI;
    using WiFiScanClass::BSSID;
    using WiFiScanClass::BSSIDstr;
    using WiFiScanClass::channel;
    void printDiag(Print& dest){}*/

public:
    friend class WiFiClient;
    friend class WiFiServer;
    friend class WiFiUDP;

    WiFiClass() {}
    void begin(const char* inSsid, const char* inPassword) {}

    void config(IPAddress local_ip) {}
    void config(IPAddress local_ip, IPAddress dns_server) {}
    void config(IPAddress local_ip, IPAddress dns_server, IPAddress gateway) {}
    void config(IPAddress local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet) {}

    int status() { return WL_CONNECT_FAILED; }
    int disconnect(bool arg) { return 0; }
    IPAddress localIP() { return INADDR_NONE; }
};

extern WiFiClass WiFi;

#endif
