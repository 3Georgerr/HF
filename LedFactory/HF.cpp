/*  HF - High Flow WS2811 LED Library
Copyright (c) 2017 Jiri seda

*/

#include "HF.h"

HF::HF(uint16_t n,uint8_t p = 6)
{
	leds = new CRGB[n];

	
	for (int i = 0; i < n; i++)
	{
		leds[i] = CRGB::Purple;
	}

	numPix = n;

	lastBlink = millis();

	mode = 1;
	changedMode = false;

	change = true;
	blinkColorOne = CRGB(255, 0, 0);
	blinkColorTwo = CRGB(0,0,0);
	blinkDelay = 500;

	svit = true;
	startDelay = 1000;

	//Startuj
	startTime;
	startColorOne = CRGB(255, 0, 0);
	startColorTwo = CRGB(255, 0, 0);
	startColorThree = CRGB(255, 0, 0);

	startColorOne = CRGB(255, 0, 0);
	startColorTwo = CRGB(255, 0, 0);
	startColorThree = CRGB(255, 0, 0);
	startPhase = 0;

		confColor = CRGB(255,0,0);
}

CRGB HF::Color(uint8_t red, uint8_t green, uint8_t blue) {
	return CRGB(red, green, blue);
}

void HF::blinkColor(uint8_t redFirst, uint8_t greenFirst, uint8_t blueFirst) {
	blinkColorOne = CRGB(redFirst, greenFirst, blueFirst);
}
void HF::blinkColor(uint8_t redFirst, uint8_t greenFirst, uint8_t blueFirst, uint8_t redSecond, uint8_t greenSecond, uint8_t blueSecond) {
	blinkColorOne = CRGB(redFirst, greenFirst, blueFirst);
	blinkColorTwo = CRGB(redSecond, greenSecond, blueSecond);
}

void HF::blikej() {
	//Hlídá interval pro zmìnu stavu
	if (lastBlink + blinkDelay<=millis()) {
		change = true;
		lastBlink = millis();
	}
	//Pokud se zmìnil stav, rozsvítí/zhasne pásek
	if (change == true) {
		change = false;
		if (svit == true) {
			fill_solid(&(leds[0]), numPix, blinkColorOne);
		}
		else {
			fill_solid(&(leds[0]), numPix, blinkColorTwo);
		}
		svit = !svit;
	}
}

void HF::startuj() {
	if (startTime + startDelay <= millis()) {
		change = true;
	}

	if (change == true) {
		change = false;
		startTime = millis();

		switch (startPhase) {
		case 0:
			fill_solid(&(leds[0]), numPix*0.33, startColorOne);
			fill_solid(&(leds[ulong(1+numPix*0.33)]), numPix- 1 + numPix*0.33, CRGB(0,0,0));
			break;
		case 1:
			fill_solid(&(leds[0]), numPix*0.66, startColorTwo);
			fill_solid(&(leds[ulong(1 + numPix*0.66)]), numPix - 1 + numPix*0.66, CRGB(0,0,0));
			break;
		case 2:
			fill_solid(&(leds[0]), numPix, startColorThree);
			break;
		default:
		//Po odstartování vypne pásek;
			setMode(0);
			startPhase = 0;
			break;
		}
		startPhase++;
	}
}

void HF::vypnout()
{
	if (changedMode || (millis() % REFRESH_RATE) ) {
		fill_solid(&(leds[0]), numPix, CRGB(0,0,0));
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
	if (changedMode || (millis() % REFRESH_RATE)) {
		fill_solid(&(leds[0]), numPix, confColor);
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
	confColor = CRGB(r,g,b);
}


int HF::getNumOfPixels()
{
	return numPix;
}

CRGB * HF::getLedArray()
{
	return leds;
}
