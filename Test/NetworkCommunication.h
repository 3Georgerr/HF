// NetworkCommunication.h
#pragma once
#ifndef _NETWORKCOMMUNICATION_h
#define _NETWORKCOMMUNICATION_h

#include <SPI.h>
#include <UIPEthernet.h>

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#endif

class NetworkCommunication {
private:
	EthernetServer server = EthernetServer(80);
	IPAddress myIP = myIP;
	uint8_t mac[6];
public:
	//mac { 0x00,0x01,0x02,0x03,0x04,0x05 }
	NetworkCommunication(IPAddress myIP, uint8_t mac[6]);
	void percentDecode(char *src);
	int parseUrlParams(char *queryString, char *results[][2], int resultsMaxCt, boolean decodeUrl);
	void loop();

};