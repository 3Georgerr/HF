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
	uint8_t macAddress[6]; // = { 0x00,0x01,0x02,0x03,0x04,0x05 };

	uint16_t numLed[6];
	uint8_t numOfStrips;

	AT24C32 eeprom;
	
	File sdConfiguration;

	boolean sdAvailable;
	boolean gotData;

public:
	void initialize(uint8_t eepromAddress=7);

	void setParameters(char ** array, uint8_t size, uint8_t NumOfparams);
	void setStrip(char ** array, uint8_t NumOfparams);

	void setIP(char * array);


	//Returns
	IPAddress getIP();
	void getMAC(uint8_t mac[]);

	//EEPROM
	void writeIPToEEPROM(uint16_t offset = 0);
	void readIPFromEEPROM(uint16_t offset = 0);
	
	void writeMACToEEPROM(uint16_t offset = 4);
	void readMACFromEEPROM(uint16_t offset = 0);
	
	void setMac(char * array);

	//SD CARD
	bool ReadFromSDCard(char *file);

	Configuration();
	~Configuration();
};

