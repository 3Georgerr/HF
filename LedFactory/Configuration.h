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
#define NUMOFSTRIPS 6

#define IPOFFSET 0
#define MACOFFSET 16
#define STRIPOFFSET 22

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

	//EEPROM
	void writeIPToEEPROM(uint16_t offset = IPOFFSET);
	void writeIPToEEPROM(uint16_t offset, IPAddress &ipToWrite);

	void writeMACToEEPROM(uint16_t offset = MACOFFSET);
	void readIPFromEEPROM(IPAddress * target, uint16_t offset=IPOFFSET );
	void readMACFromEEPROM(uint16_t offset = MACOFFSET);

	void writeNumOfLedsToEEPROM(uint8_t strip, uint16_t offset = STRIPOFFSET);
	void readNumOfLedsFromEEPROM(uint8_t strip, uint16_t offset = STRIPOFFSET);



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

	void reset();

	void overrideNumOfLedsToEEPROM(uint8_t strip, uint16_t numOfLeds, uint16_t offset=22);
	void overrideIPToEEPROM(char * array, uint16_t offset = 22);


	//SD CARD
	bool ReadFromSDCard(char *file);

	Configuration();
	~Configuration();
	
};

