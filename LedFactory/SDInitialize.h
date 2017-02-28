#pragma once
#ifndef _SDINITIALIZE_h
#define _SDINITIALIZE_h
#include <SPI.h>
#include <UIPEthernet.h>
#endif

class SDInitialize
{
private:
	static IPAddress ip;
	static uint8_t macAddress[6]; // = { 0x00,0x01,0x02,0x03,0x04,0x05 };

	static uint16_t numLedFirst;
	static uint16_t numLedSecond;
	static uint16_t numLedThird;
	static uint16_t numLedFourth;
	static uint16_t numLedFifth;
	static uint16_t numLedSixth;


public:
	static void initialize();
	SDInitialize();
	~SDInitialize();
};

