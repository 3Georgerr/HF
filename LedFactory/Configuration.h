#pragma once
#ifndef _CONFIGURATION_h
#define _CONFIGURATION_h
#include <SPI.h>
#include <Ethernet.h>
#include <AT24CX.h>
#include <SD.h>
#endif

//CS pin SD card
#define CSPINSDCARD 3
#define NUMOFSTRIPS 6;

class Configuration
{
private:
	IPAddress ip;
	IPAddress gateway;
	IPAddress dns;
	IPAddress subnet;
	uint8_t macAddress[6]; // = { 0x00,0x01,0x02,0x03,0x04,0x05 };

	uint16_t numLed[6];
	uint8_t numOfStrips;

	AT24C32 eeprom;
	
	File sdConfiguration;

	boolean sdAvailable;
	boolean gotData;

public:
	void initialize(uint8_t eepromAddress=7);

	void setParameters(char array[4][31], uint8_t NumOfparams);
	
	void setStrip(char array[3][31], uint8_t NumOfparams);

	void setIP(char * array);
	void setSubnet(char * array);
	void setGateway(char * array);
	void setDNS(char * array);
	void setMac(char * array);

	//Returns
	IPAddress getIP();
	IPAddress getSubnet();
	IPAddress getGateway();
	IPAddress getDNS();
	void getMAC(uint8_t mac[]);
	int getNumOfLed(uint8_t strip);

	//EEPROM
	void writeIPToEEPROM(uint16_t offset = 0);
	void writeIPToEEPROM(uint16_t offset, IPAddress &ipToWrite);
	
	void writeMACToEEPROM(uint16_t offset = 16);
	void readIPFromEEPROM(uint16_t offset, IPAddress * target);
	void readMACFromEEPROM(uint16_t offset = 16);

	void writeNumOfLedsToEEPROM(uint8_t strip, uint16_t offset=22);
	void readNumOfLedsFromEEPROM(uint8_t strip, uint16_t offset=22);
	
	//SD CARD
	bool ReadFromSDCard(char *file);

	Configuration();
	~Configuration();
	
};

