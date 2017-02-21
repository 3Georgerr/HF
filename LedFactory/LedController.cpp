// 
// 
// 

#include "LedController.h"

LedController::LedController(uint8_t numOfStrips)
{
	ledPasek = new HF*[numOfStrips];
	//this->ledPasek = ledPasek;
}
HF * LedController::getStrip(uint8_t numOfStrip)
{
	return ledPasek[numOfStrip];
}

void LedController::setStrip(HF * strip, uint8_t numOfStrip)
{
	ledPasek[numOfStrip] = strip;
}