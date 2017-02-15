/*  HF - High Flow WS2811 LED Library
Copyright (c) 2017 Jiri seda

*/
#pragma once
#ifndef HF_h
#define HF_h
#endif

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


#define	turnedOff	0
#define	blinking	1
#define	starting	2
#define	lighting	3


class HF {
private:
	// Parameter 1 = number of pixels in strip
	// Parameter 2 = pin number (most are valid)
	// Parameter 3 = pixel type flags, add together as needed:
	//   NEO_RGB     Pixels are wired for RGB bitstream
	//   NEO_GRB     Pixels are wired for GRB bitstream
	//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
	//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)

	Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 6, NEO_GRB + NEO_KHZ800);
	uint16_t numPix;
	//mode 0 = vypnuto
	//mode 1 = blinking
	//mode 2 = starting
	//mode 3 = light
	uint8_t mode = 1;
	static const uint32_t REFRESH_RATE = 1000;
	boolean changedMode = false;

	unsigned long lastBlink;
	boolean change = true;
	uint32_t blinkDelay = 500;
	uint32_t blinkColorOne = 255000000;
	uint32_t blinkColorTwo = 000000000;

	boolean svit = true;
	uint32_t startDelay = 1000;

	//Startuj
	unsigned long startTime;
	uint32_t startColorOne = 255128128;
	uint32_t startColorTwo = 255128128;
	uint32_t startColorThree = 255128128;
	uint8_t startPhase = 0;

	uint32_t confColor=255128128;

public:
	HF(uint16_t n, uint8_t p = 6, uint8_t t = NEO_GRB + NEO_KHZ800)
	{
		strip = Adafruit_NeoPixel(n, p, t);
		lastBlink = millis();
		strip.begin();
		numPix = strip.numPixels();
	}

	uint32_t color(uint8_t red, uint8_t green, uint8_t blue) {
		return (red << 16) | (green << 8) | blue;
	}
	
	void blikej();
	void startuj();
	void vypnout();
	void loop();
	void light();

	void setMode(uint8_t mode);
	void setColor(uint8_t r, uint8_t g, uint8_t b);
	
	/**
	Spustí zobrazení na pásek, citlivé na pøesnost rychlosti pøenosu
	*/
	void showIt();

};
