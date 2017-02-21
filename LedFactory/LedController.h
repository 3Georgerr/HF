// controller.h

#ifndef _CONTROLLER_h
#define _CONTROLLER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "HF.h"

#endif


class LedController {
private:
	//pro nastaveni pasku
	HF **ledPasek;
public:
	LedController(uint8_t numOfStrips);
	void setStrip(HF *strip, uint8_t numOfStrip);
	HF* getStrip(uint8_t numOfStrip);


};