/*  HF - High Flow WS2811 LED Library
Copyright (c) 2017 Jiri seda

*/

#include "HF.h"

HF::HF(uint16_t n, uint8_t p = 6, uint8_t t = NEO_GRB + NEO_KHZ800)
{
	strip = Adafruit_NeoPixel(n, p, t);
	numPix = n;

	lastBlink = millis();

	mode = 1;
	changedMode = false;

	change = true;
	blinkColorOne = 16711680;
	blinkColorTwo = 0;
	blinkDelay = 500;

	svit = true;
	startDelay = 1000;

	//Startuj
	startTime;
	startColorOne = 16744576;
	startColorTwo = 16744576;
	startColorThree = 16744576;

	startColorOne = 16711680;
	startColorTwo = 16711680;
	startColorThree = 16711680;
	startPhase = 0;

	//	confColor = color(255,000,000);
	confColor = 16711680; //nefunguje?

	strip.begin();
	//	confColor = color(255,0,0);
}

uint32_t HF::color(uint8_t red, uint8_t green, uint8_t blue) {
	return (red << 16) | (green << 8) | blue;
}

void HF::blinkColor(uint8_t redFirst, uint8_t greenFirst, uint8_t blueFirst) {
	blinkColorOne = color(redFirst, greenFirst, blueFirst);
}
void HF::blinkColor(uint8_t redFirst, uint8_t greenFirst, uint8_t blueFirst, uint8_t redSecond, uint8_t greenSecond, uint8_t blueSecond) {
	blinkColorOne = color(redFirst, greenFirst, blueFirst);
	blinkColorTwo = color(redSecond, greenSecond, blueSecond);
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
			//for (uint16_t i = 0; i<strip.numPixels(); i++) {
			//	strip.setPixelColor(i, blinkColorOne);
			//}
			strip.setStripColor(blinkColorOne);
		}
		else {
			//for (uint16_t i = 0; i<strip.numPixels(); i++) {
			//	strip.setPixelColor(i, blinkColorTwo);
			//}
			strip.setStripColor(blinkColorTwo);
		}
		//strip.show();
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
			for (uint16_t i = 0; i < numPix*0.33; i++) {
				strip.setPixelColor(i, startColorOne);
			}
			for (uint16_t i = numPix*0.33; i < numPix; i++) {
				strip.setPixelColor(i, strip.Color(0, 0, 0));
			}
			break;
		case 1:
			for (uint16_t i = 0; i < numPix*0.66; i++) {
				strip.setPixelColor(i, startColorTwo);
			}
			for (uint16_t i = numPix*0.66; i < numPix; i++) {
				strip.setPixelColor(i, strip.Color(0, 0, 0));
			}
			break;
		case 2:
			//for (uint16_t i = 0; i < numPix; i++) {
			//	strip.setPixelColor(i, startColorThree);
			//}
			strip.setStripColor(startColorThree);
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
		//for (uint16_t i = 0; i < numPix; i++) {
		//	strip.setPixelColor(i, strip.Color(0, 0, 0));
		//}
		strip.setStripColor(strip.Color(0, 0, 0));
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
	if (changedMode || (millis() % REFRESH_RATE)) {
		//for (uint16_t i = 0; i < numPix; i++) {
			//strip.setPixelColor(i, confColor);
		//}
		strip.setStripColor(confColor);
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

int HF::getNumOfPixels()
{
	return numPix;
}
