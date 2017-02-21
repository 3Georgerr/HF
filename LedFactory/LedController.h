// controller.h

#ifndef _CONTROLLER_h
#define _CONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "HF.h"
#include "NetworkCommunication.h"

#endif


class LedController {
private:
	//pro nastaveni pasku
	HF **ledStrips;
	NetworkCommunication *nc;
public:
	LedController(uint8_t numOfStrips);
	void setStrip(HF *strip, uint8_t numOfStrip);
	void setNetworkcommunication(NetworkCommunication *nc);
	HF* getStrip(uint8_t numOfStrip);
	NetworkCommunication* getNetworkCommunication();


};