/*  HF - High Flow WS2811 LED Library
Copyright (c) 2017 Jiri seda
*/

#include "HF.h"


HF::HF(uint16_t n,uint8_t p = 6)
{
	leds = new CRGB[n];

	
	for (int i = 0; i < n; i++)
	{
		leds[i] = CRGB::Black;
	}

	numPix = n;

	lastBlink = 0;

	mode = 4;
	changedMode = false;

	//parametry blikani
	lightOn = true;
	change = true;
	blinkColorOne = CRGB(10, 0, 0);
	blinkColorTwo = CRGB(0,0,0);
	blinkDelay = 500;
	

	//Startuj
	startTime=0;
	startDelay = 1000;
	startColorOne = CRGB(255, 0, 0);
	startColorTwo = CRGB(255, 0, 0);
	startColorThree = CRGB(255, 0, 0);
	startPhase = 0;

	confColor = CRGB(255,0,0);
}

HF::~HF()
{
	delete leds;
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

void HF::blink() {
	//Hlídá interval pro zmìnu stavu
	if (millis() - lastBlink > blinkDelay) {
		change = true;
		lastBlink = millis();
	}
	//Pokud se zmìnil stav, rozsvítí/zhasne pásek
	if (change == true) {
		change = false;
		if (lightOn == true) {
			fill_solid(&(leds[0]), numPix, blinkColorOne);
		}
		else {
			fill_solid(&(leds[0]), numPix, blinkColorTwo);
		}

		lightOn = !lightOn;
	}
	
}

void HF::blinkDuo()
{
	//Hlídá interval pro zmìnu stavu
	if (millis() - lastBlink > blinkDelay ) {
		change = true;
		lastBlink = millis();
	}
	//Pokud se zmìnil stav, rozsvítí/zhasne pásek
	if (change == true) {
		change = false;
		if (lightOn == true) {
			for (int i = 0; i <numPix; i +=2) {
				leds[i] = blinkColorOne;
			}
			for (int i = 1; i<numPix; i +=2) {
				leds[i] = blinkColorTwo;
			}
		}
		else {
			for (int i = 0; i<numPix; i +=2) {
				leds[i] = blinkColorTwo;
			}
			for (int i = 1; i < numPix; i+=2) {
				leds[i] = blinkColorOne;
			}
		}
		lightOn = !lightOn;
	}
}

void HF::start() {
	if (millis() - startTime > startDelay) {
		change = true;
	}

	if (change == true) {
		change = false;
		startTime = millis();
		
		switch (startPhase) {
		case 0:
			fill_solid(&(leds[0]), numPix/3, startColorOne);
			fill_solid(&(leds[ulong(numPix/3)]), numPix - numPix/3, CRGB(0,0,0));
			break;
		case 1:
			fill_solid(&(leds[0]), numPix*0.66, startColorTwo);
			fill_solid(&(leds[ulong((numPix/3)*2)]), numPix - (numPix/3)*2, CRGB(0,0,0));
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

void HF::turnOff()
{
	if (changedMode || (millis() % REFRESH_RATE) ) {
		fill_solid(&(leds[0]), numPix, CRGB(0,0,0));
	}
}

//mode 0 = vypnuto
//mode 1 = light
//mode 2 = starting
//mode 3 = blinking
//mode 4 = blinkDuo
void HF::loop() {
	switch (mode) {
	case 0:
		turnOff();
		break;
	case 1:
		light();
		break;
	case 2:
		start();
		break;
	case 3:
		blink();
		break;
	case 4:
		blinkDuo();
		break;
	default:
		turnOff();
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

		change = true;
		lightOn = true;
		startPhase = 0;
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

void HF::decodeColor(char *color)
{
	uint16_t values[9];

	//mode 0 = vypnuto
	//mode 1 = light
	//mode 2 = starting
	//mode 3 = blinking
	//mode 4 = blinkung duo
	switch (mode) {
	case 0:
		break;
	case 1:
		if (3 == sscanf(color, "%d:%d:%d%c", &values[0], &values[1], &values[2])) {
			if (values[0] < 256 && values[1] < 256 && values[2] < 256) {
			setColor(values[0], values[1], values[2]);
		}
		}
		break;
	case 2:
		if (3 == sscanf(color, "%d:%d:%d,%d:%d:%d,%d:%d:%d%c", &values[0], &values[1], &values[2], &values[3], &values[4], &values[5], &values[6], &values[7], &values[8])) {
			if (values[0] < 256 && values[1] < 256 && values[2] < 256) {
				startColorOne = CRGB(values[0], values[1], values[2]);
				startColorTwo = CRGB(values[0], values[1], values[2]);
				startColorThree = CRGB(values[0], values[1], values[2]);
			}
		}
		else if (9 == sscanf(color, "%d:%d:%d,%d:%d:%d,%d:%d:%d%c", &values[0], &values[1], &values[2], &values[3], &values[4], &values[5], &values[6], &values[7], &values[8])) {
			if (values[0] < 256 && values[1] < 256 && values[2] < 256 && values[3] < 256 && values[4] < 256 && values[5] < 256 && values[6] < 256 && values[7] < 256 && values[8] < 256) {
				startColorOne = CRGB(values[0], values[1], values[2]);
				startColorTwo = CRGB(values[3], values[4], values[5]);
				startColorThree = CRGB(values[6], values[7], values[8]);
				Serial.print(values[0]);
				Serial.print(",");
				Serial.print(values[1]);
				Serial.print(",");
				Serial.println(values[2]);
				Serial.print(values[3]);
				Serial.print(",");
				Serial.print(values[4]);
				Serial.print(",");
				Serial.println(values[5]);
			}
		}
		break;
	case 3:
	case 4:
		 if (3 == sscanf(color, "%d:%d:%d,%d:%d:%d,%d:%d:%d%c", &values[0], &values[1], &values[2], &values[3], &values[4], &values[5], &values[6], &values[7], &values[8])) {
			Serial.println("NE");
			if (values[0] < 256 && values[1] < 256 && values[2] < 256) {
				blinkColorOne = CRGB(values[0], values[1], values[2]);
			}
		}else if (6 == sscanf(color, "%d:%d:%d,%d:%d:%d%c", &values[0], &values[1], &values[2], &values[3], &values[4], &values[5])) {
			Serial.println("OK");
			if (values[0] < 256 && values[1] < 256 && values[2] < 256 && values[3] < 256 && values[4] < 256 && values[5] < 256) {
				blinkColorOne = CRGB(values[0], values[1], values[2]);
				blinkColorTwo = CRGB(values[3], values[4], values[5]);
			}
		}
		
		
		break;
	default:
		break;
	}
}