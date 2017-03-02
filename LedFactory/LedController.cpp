// 
// 
// 

#include "LedController.h"

LedController::LedController(uint8_t numOfStrips)
{
	ledStrips = new HF*[numOfStrips];
	this->numOfStrips = numOfStrips;
}

HF * LedController::getStrip(uint8_t numOfStrip)
{
	return ledStrips[numOfStrip];
}

NetworkCommunication * LedController::getNetworkCommunication()
{
	return nc;
}

void LedController::loop()
{
	nc->loop();
	for (int i = 0; i < numOfStrips; i++) {
		ledStrips[i]->loop();
	}
}

void LedController::getParams()
{
	nc->getResults();
}

void LedController::setStrip(HF * strip, uint8_t numOfStrip)
{
	ledStrips[numOfStrip] = strip;
}

void LedController::setNetworkcommunication(NetworkCommunication & nc)
{
	this->nc = &nc;
}
