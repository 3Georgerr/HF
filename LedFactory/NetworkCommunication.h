// NetworkCommunication.h
#pragma once
#ifndef _NETWORKCOMMUNICATION_h
#define _NETWORKCOMMUNICATION_h

#include <SPI.h>
#include <Ethernet.h>
//#include <UIPEthernet.h>
#include "HF.h"
#include "Configuration.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#endif

class NetworkCommunication {
private:
	EthernetServer server = EthernetServer(80);
	IPAddress myIP;
	IPAddress myDNS;
	IPAddress myGateway;
	IPAddress mySubnet;
	uint8_t mac[6];
	char clientline[BUFSIZ];
	int index;


	uint8_t resultsCt;
	char *params[16][2];

	HF **ledStrips;
	uint8_t numOfStrips = 0;

	//Nastavovaci cast
	HF *activeStrip;
	Configuration *config;

public:
	//mac { 0x00,0x01,0x02,0x03,0x04,0x05 }
	NetworkCommunication(uint8_t numOfStrips,uint8_t mac[6], IPAddress myIP,IPAddress myDNS,IPAddress myGateway,IPAddress mySubnet);
	void percentDecode(char *src);
	int parseUrlParams(char *queryString, char *results[][2], int resultsMaxCt, boolean decodeUrl);
	void loop();
	void start();
//	void setStrip(HF *strip, uint8_t numOfStrip);
  //  HF* getStrip(uint8_t numOfStrip);
	uint8_t getResults();

	void decodeParams(char *results[][2], uint8_t numOfResults);
	void setStrip(HF *strip, uint8_t numOfStrip);
	void setConfig(Configuration *config);

	//void setStrip

};