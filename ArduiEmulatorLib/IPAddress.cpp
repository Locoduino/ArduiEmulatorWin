/*
IPAddress.h - Base class that provides IPAddress
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

#include "IPAddress.hpp"
//#include "Printable.h"
//#include "WString.h"

// A class to make it easier to handle and pass around IP addresses

void IPAddress::bytesToDword()
	{
		uint32_t address = 0;
		uint32_t factor = 1;

		for (int i = 3; i > 0; --i) {
			address += this->bytes[i] * factor;
			address *= 256;
		}
	}

void IPAddress::DwordToBytes()
	{
		uint32_t address = this->dword;

		for (int i = 3; i > 0; --i) {
			this->bytes[i] = address % 256;
			address /= 256;
		}
	}

IPAddress::IPAddress()
	{
		//this->bytes = gcnew array<uint8_t>(4);
		this->dword = 0;
	}

IPAddress::IPAddress(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet)
	{
		this->bytes[0] = first_octet;
		this->bytes[1] = second_octet;
		this->bytes[2] = third_octet;
		this->bytes[3] = fourth_octet;
		bytesToDword();
	}

IPAddress::IPAddress(uint32_t address)
	{
		this->dword = address;
		DwordToBytes();
	}

IPAddress::IPAddress(const uint8_t *address)
	{
		this->bytes[0] = address[0];
		this->bytes[1] = address[1];
		this->bytes[2] = address[2];
		this->bytes[3] = address[3];
		bytesToDword();
	}

IPAddress::IPAddress(const IPAddress &address)
	{
		this->dword = address.dword;
		DwordToBytes();
	}

IPAddress::operator uint32_t() { return this->dword; };
bool IPAddress::operator==(IPAddress addr) { return dword == addr.dword; };
bool IPAddress::operator==(const uint8_t* addr)
	{
		return this->bytes[0] == addr[0] && this->bytes[1] == addr[1] &&
			this->bytes[2] == addr[2] && this->bytes[3] == addr[3];
	}

	// Overloaded index operator to allow getting and setting individual octets of the address
uint8_t IPAddress::operator[](int index)
	{
		return this->bytes[index];
	}

	// Overloaded copy operators to allow initialisation of IPAddress objects from other types
IPAddress &IPAddress::operator=(const uint8_t *address) {
		this->bytes[0] = address[0];
		this->bytes[1] = address[1];
		this->bytes[2] = address[2];
		this->bytes[3] = address[3];
		//memcpy(_address.bytes, address, sizeof(_address.bytes));
		this->bytesToDword();

		return *this;
	}

	//IPAddress operator=(const uint8_t *address);
IPAddress &IPAddress::operator=(uint32_t address)
	{
		this->dword = address;
		this->DwordToBytes();

		return *this;
	}
