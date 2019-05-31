#include "Ethernet.hpp"

EthernetClass::EthernetClass() {
		this->dhcp = false;
		//this->mac = gcnew array<uint8_t>(6);
	}

int EthernetClass::begin(const uint8_t* inmac) {
		for (int i = 0; i < 6; i++)
			mac[i] = inmac[i];
		ip = IPAddress(0, 0, 0, 0);
		dhcp = true;
		subnet = IPAddress(255, 255, 255, 0);
		gateway = IPAddress(0, 0, 0, 0);
		dns = IPAddress(0, 0, 0, 0);
		return 0;
	}

void EthernetClass::begin(const uint8_t* inmac, IPAddress inip) {
		for (int i = 0; i < 6; i++)
			mac[i] = inmac[i];
		ip = inip;

		if (uint32_t(ip) == 0)
			dhcp = true;

		subnet = IPAddress(255, 255, 255, 0);
		gateway = IPAddress(0, 0, 0, 0);
		dns = IPAddress(0, 0, 0, 0);
	}

void EthernetClass::begin(const uint8_t* inmac, IPAddress inip, IPAddress indns) {
		for (int i = 0; i < 6; i++)
			mac[i] = inmac[i];
		ip = inip;

		if (uint32_t(ip) == 0)
			dhcp = true;

		subnet = IPAddress(255, 255, 255, 0);
		gateway = IPAddress(0, 0, 0, 0);
		dns = indns;
	}

void EthernetClass::begin(const uint8_t* inmac, IPAddress inip, IPAddress indns, IPAddress ingateway) {
		for (int i = 0; i < 6; i++)
			mac[i] = inmac[i];
		ip = inip;

		if (uint32_t(ip) == 0)
			dhcp = true;

		subnet = IPAddress(255, 255, 255, 0);
		gateway = ingateway;
		dns = indns;
	}

void EthernetClass::begin(const uint8_t* inmac, IPAddress inip, IPAddress indns, IPAddress ingateway, IPAddress insubnet) {
		for (int i = 0; i < 6; i++)
			mac[i] = inmac[i];
		ip = inip;

		if (uint32_t(ip) == 0)
			dhcp = true;

		subnet = insubnet;
		gateway = ingateway;
		dns = indns;
	}

int EthernetClass::maintain() { return 0; }

IPAddress EthernetClass::localIP() { return this->ip; }
IPAddress EthernetClass::subnetMask() { return this->subnet; }
IPAddress EthernetClass::gatewayIP() { return this->gateway; }
IPAddress EthernetClass::dnsServerIP() { return this->dns; }

/***********************************************************
		EthernetClient
************************************************************/

EthernetClient::EthernetClient() {}
EthernetClient::EthernetClient(uint8_t sock) { _sock = sock; }

uint8_t EthernetClient::status() { return 0; }
int EthernetClient::connect(IPAddress ip, uint16_t port) { return 0; }
int EthernetClient::connect(const char *host, uint16_t port) { return 0; }
size_t EthernetClient::write(uint8_t) { return 0; }
size_t EthernetClient::write(const uint8_t *buf, size_t size) { return 0; }
int EthernetClient::available() { return 0; }
int EthernetClient::read() { return 0; }
int EthernetClient::read(uint8_t *buf, size_t size) { return 0; }
int EthernetClient::peek() { return 0; }
void EthernetClient::flush() { }
void EthernetClient::stop() { }
uint8_t EthernetClient::connected() { return 0; }
EthernetClient::operator bool() { return false; }
bool EthernetClient::operator==(const bool value) { return bool() == value; }
bool EthernetClient::operator!=(const bool value) { return bool() != value; }
bool EthernetClient::operator==(const EthernetClient&) { return false; }
bool EthernetClient::operator!=(const EthernetClient &rhs) { return !this->operator==(rhs); };
uint8_t EthernetClient::getSocketNumber() { return _sock; }

/***********************************************************
EthernetServer
************************************************************/

EthernetServer::EthernetServer(uint16_t inPort) { _port = inPort; }
EthernetClient *EthernetServer::available() { return new EthernetClient(0); }
void EthernetServer::begin() {}
size_t EthernetServer::write(uint8_t) { return 0; }
size_t EthernetServer::write(const uint8_t *buf, size_t size) { return 0; }
	//using Print::write;

void EthernetServer::print(const char *line) {}
void EthernetServer::println(const char *line) {}
//void EthernetServer::print(String^ line) {}
//void EthernetServer::println(String^ line) {}
void EthernetServer::print(int value) {}
void EthernetServer::print(int value, int i) {}
void EthernetServer::println(int value) {}
void EthernetServer::println(int value, int i) {}

