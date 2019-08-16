//-------------------------------------------------------------------
#ifndef __ethernet_Hpp__
#define __ethernet_Hpp__
//-------------------------------------------------------------------

//#include "Dhcp.h"
#include "Arduino.h"
#include "IPAddress.hpp"

class EthernetClass
{
private:
	uint8_t mac[6];
	IPAddress ip;
	IPAddress subnet;
	IPAddress gateway;
	IPAddress dns;
	bool dhcp;

public:
	static EthernetClass EthernetInstance;

	EthernetClass();
	int begin(const uint8_t* inmac);
	void begin(const uint8_t* inmac, IPAddress inip);
	void begin(const uint8_t* inmac, IPAddress inip, IPAddress indns);
	void begin(const uint8_t* inmac, IPAddress inip, IPAddress indns, IPAddress ingateway);
	void begin(const uint8_t* inmac, IPAddress inip, IPAddress indns, IPAddress ingateway, IPAddress insubnet);

	// maintain() must be called at regular intervals to process the incoming serial
	// data and issue IP events to the sketch.  It does not return until all IP
	// events have been processed. Renews dhcp-lease if required.
	int maintain();

	IPAddress localIP();
	IPAddress subnetMask();
	IPAddress gatewayIP();
	IPAddress dnsServerIP();
};

#define Ethernet EthernetClass::EthernetInstance

class EthernetClient {

private:
	static uint16_t _srcport;
	uint8_t _sock;

public:
	EthernetClient();
	EthernetClient(uint8_t sock);

	uint8_t status();
	int connect(IPAddress ip, uint16_t port);
	int connect(const char *host, uint16_t port);
	size_t write(uint8_t);
	size_t write(const uint8_t *buf, size_t size);
	int available();
	int read();
	int read(uint8_t *buf, size_t size);
	int peek();
	void flush();
	void stop();
	uint8_t connected();
	operator bool();
	bool operator==(const bool value);
	bool operator!=(const bool value);
	bool operator==(const EthernetClient &);
	bool operator!=(const EthernetClient &rhs);
	uint8_t getSocketNumber();

	//friend class EthernetServer;

	//using Print::write;
};

class EthernetServer {
private:
	uint16_t _port;
public:
	EthernetServer(uint16_t inPort);
	EthernetClient &available();
	void begin();
	size_t write(uint8_t);
	size_t write(const uint8_t *buf, size_t size);
	//using Print::write;

	void print(const char *line);
	void println(const char *line);
	//void print(String &line);
	//void println(String &line);
	void print(int value);
	void print(int value, int i);
	void println(int value);
	void println(int value, int i);
};

#define Ethernet EthernetClass::EthernetInstance

//-------------------------------------------------------------------
#endif
//-------------------------------------------------------------------