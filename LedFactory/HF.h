/*  HF - High Flow WS2811 LED Library
Copyright (c) 2017 Jiri seda

*/
#pragma once
#ifndef HF_h
#define HF_h
#endif

#include <Arduino.h>
#include <FastLED\FastLED.h>


#define	turnedOff	0
#define	blinking	1
#define	starting	2
#define	lighting	3
#define REFRESH_RATE 1000

class HF {
private:
	// Parameter 1 = number of pixels in strip
	// Parameter 2 = pin number (most are valid)

	CRGB *leds;
	
	uint16_t numPix;
	//mode 0 = vypnuto
	//mode 1 = blinking
	//mode 2 = starting
	//mode 3 = light
	uint8_t mode;
	//static const uint32_t REFRESH_RATE = 1000;
	boolean changedMode;

	uint32_t lastBlink;
	boolean change;
	uint32_t blinkDelay;
	CRGB blinkColorOne;
	CRGB blinkColorTwo;

	boolean svit;
	uint32_t startDelay;

	//Startuj
	unsigned long startTime;
	CRGB startColorOne;
	CRGB startColorTwo;
	CRGB startColorThree;
	uint8_t startPhase;

	CRGB confColor;
	
	
	

public:
	HF(uint16_t n, uint8_t p);

	CRGB Color(uint8_t red, uint8_t green, uint8_t blue);

	void blinkColor(uint8_t redFirst, uint8_t greenFirst, uint8_t blueFirst);
	void blinkColor(uint8_t redFirst, uint8_t greenFirst, uint8_t blueFirst, uint8_t redSecond, uint8_t greenSecond, uint8_t blueSecond);
	
	void blikej();
	void startuj();
	void vypnout();
	void loop();
	void light();

	void setMode(uint8_t mode);
	void setColor(uint8_t r, uint8_t g, uint8_t b);
	

	int getNumOfPixels();
	CRGB* getLedArray();

};
