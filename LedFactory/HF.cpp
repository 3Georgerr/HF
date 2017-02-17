/*  HF - High Flow WS2811 LED Library
Copyright (c) 2017 Jiri seda

*/

#include "HF.h"


void HF::blikej() {
	//Hlídá interval pro zmìnu stavu
	if (lastBlink + blinkDelay<millis()) {
		change = true;
		lastBlink = millis();
	}
	//Pokud se zmìnil stav, rozsvítí/zhasne pásek
	if (change == true) {
		change = false;
		if (svit == true) {
			for (uint16_t i = 0; i<strip.numPixels(); i++) {
				strip.setPixelColor(i, blinkColorOne);
			}
		}
		else {
			for (uint16_t i = 0; i<strip.numPixels(); i++) {
				strip.setPixelColor(i, blinkColorTwo);
			}
		}
		//strip.show();
		svit = !svit;
	}
}

void HF::startuj() {
	if (startTime + startDelay < millis()) {
		change = true;
	}

	if (change == true) {
		change = false;
		startTime = millis();

		switch (startPhase) {
		case 0:
			for (uint16_t i = 0; i < numPix*0.33; i++) {
				strip.setPixelColor(i, startColorOne);
			}
			for (uint16_t i = numPix*0.33; i < numPix; i++) {
				strip.setPixelColor(i, strip.Color(0, 0, 0));
			}
			//strip.show();
			break;
		case 1:
			for (uint16_t i = 0; i < numPix*0.66; i++) {
				strip.setPixelColor(i, startColorTwo);
			}
			for (uint16_t i = numPix*0.66; i < numPix; i++) {
				strip.setPixelColor(i, strip.Color(0, 0, 0));
			}
			//strip.show();
		case 2:
			for (uint16_t i = 0; i < numPix; i++) {
				strip.setPixelColor(i, startColorThree);
			}
			//strip.show();
			break;
		default:
		//Po odstartování vypne pásek;
			setMode(0);
			break;
		}
		startPhase++;
	}
}

void HF::vypnout()
{
	if (changedMode || (millis() % REFRESH_RATE) ) {
		for (uint16_t i = 0; i < numPix; i++) {
			strip.setPixelColor(i, strip.Color(0, 0, 0));
		}
		//strip.show();
	}
}

//mode 0 = vypnuto
//mode 1 = blinking
//mode 2 = starting
//mode 3 = light
void HF::loop() {
	switch (mode) {
	case 0:
		vypnout();
		break;
	case 1:
		blikej();
		break;
	case 2:
		startuj();
		break;
	case 3:
		light();
		break;
	default:
		break;
	}
	changedMode = false;
}

void HF::light()
{
	//Obnovuje nastavení svìtel, pokud se zmìní stav nebo uteklo 1000 sekund 
	if (changedMode || (millis() % REFRESH_RATE) ) {
		for (uint16_t i = 0; i < numPix; i++) {
			strip.setPixelColor(i, confColor);
		}
		delay(100);
		//strip.show();
	}
}

void HF::setMode(uint8_t mode)
{
	this->mode = mode;
	changedMode = true;

	if (mode == 1) {
		change = true;
		svit = true;

	}
}

void HF::setColor(uint8_t r, uint8_t g, uint8_t b)
{
	confColor = ((uint32_t)r << 16) | ((uint32_t)g << 8) | b;
}

void HF::showIt()
{
	strip.show();
}
