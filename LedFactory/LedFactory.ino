//#pragma once 
//#pragma GCC optimize ("O0")


#include "HF.h"
#include "NetworkCommunication.h"
//#include <Adafruit_NeoPixel.h>
#include <FastLED\FastLED.h>
#include "LedController.h"
//#include <Scheduler.h>

#define NUMLEDFIRST 1024
#define NUMLEDSECOND 1024
#define NUMLEDTHIRD 1024
#define NUMLEDFOURTH 1024
#define NUMLEDFIFTH 1024
#define NUMLEDSIXTH 1024

#define PINSTRIPONE 1
#define PINSTRIPTWO 6
#define PINSTRIPTHREE 2
#define PINSTRIPFOUR 3
#define PINSTRIPFIVE 4
#define PINSTRIPSIX 5


HF prvni = HF(NUMLEDFIRST, PINSTRIPONE);
HF druhy = HF(NUMLEDSECOND, PINSTRIPTWO);
HF treti = HF(NUMLEDTHIRD, PINSTRIPTHREE);
HF ctvrty = HF(NUMLEDFOURTH, PINSTRIPFOUR);
HF paty = HF(NUMLEDFIFTH, PINSTRIPFIVE);
HF sesty = HF(NUMLEDSIXTH, PINSTRIPSIX);


uint32_t counter = 0;
uint8_t mac[6] = { 0x00,0x01,0x02,0x03,0x04,0x05 };
IPAddress ip = IPAddress(10, 0, 0, 34);
NetworkCommunication nc = NetworkCommunication(mac, ip);
LedController lc = LedController(6);

uint32_t interval = 100;
uint32_t lastTime = 0;

void setup() {
	// put your setup code here, to run once:
	
	//Pro testování funkcí, neøešíme èasování

	HF prvni = HF(NUMLEDFIRST, PINSTRIPONE);
	HF druhy = HF(NUMLEDSECOND, PINSTRIPTWO);
	HF treti = HF(NUMLEDTHIRD, PINSTRIPTHREE);
	HF ctvrty = HF(NUMLEDFOURTH, PINSTRIPFOUR);
	HF paty = HF(NUMLEDFIFTH, PINSTRIPFIVE);
	HF sesty = HF(NUMLEDSIXTH, PINSTRIPSIX);


	
	FastLED.addLeds<NEOPIXEL, PINSTRIPONE>(prvni.getLedArray(), NUMLEDFIRST);
	FastLED.addLeds<NEOPIXEL, PINSTRIPTWO>(druhy.getLedArray(), NUMLEDSECOND);
	FastLED.addLeds<NEOPIXEL, PINSTRIPTHREE>(treti.getLedArray(), NUMLEDTHIRD);
	FastLED.addLeds<NEOPIXEL, PINSTRIPFOUR>(ctvrty.getLedArray(), NUMLEDFOURTH);
	FastLED.addLeds<NEOPIXEL, PINSTRIPFIVE>(paty.getLedArray(), NUMLEDFIFTH);
	FastLED.addLeds<NEOPIXEL, PINSTRIPSIX>(sesty.getLedArray(), NUMLEDSIXTH);
	

	ip = IPAddress(10, 0, 0, 34);
	nc = NetworkCommunication(mac, ip);
	
	
	lc.setStrip(&prvni, 0);
	lc.setStrip(&druhy, 1);
	lc.setStrip(&treti, 2);
	lc.setStrip(&ctvrty, 3);
	lc.setStrip(&paty, 4);
	lc.setStrip(&sesty, 5);
	lc.setNetworkcommunication(nc);
	
	
	//lc.getStrip(0)->blinkColor(0, 10, 1, 0, 1, 1);
	//lc.getStrip(0)->blinkCRGB(0, 0, 1, 0, 1, 0);
	//lc.getStrip(1)->blinkColor(1, 0, 0, 0, 0, 1);
	
	//prvni.blinkCRGB(0, 1, 1, 1, 1, 1);
	//prvni.blinkCRGB(0, 10, 1, 0, 1, 1);
	//prvni.blinkCRGB(0, 0, 255);
	//druhy.blinkCRGB(1, 0, 0, 0, 1, 0);
	//prvni.blinkCRGB(0, 0, 255, 0, 255, 0);

	nc.start();

	//Scheduler.startLoop(loop2);
}

void loop() {
	//showIT vyraznì zpomaluje
	if (lastTime+interval < millis()) {
		lastTime = millis();
		FastLED.show();
	}

	lc.getStrip(0)->loop();
	lc.getStrip(1)->loop();
	lc.getStrip(2)->loop();
	lc.getStrip(3)->loop();
	lc.getStrip(4)->loop();
	lc.getStrip(5)->loop();
	
	if (millis()%10000==1 &&  counter==0) {
		//prvni.setMode(2);
		//lc.getStrip(1)->setMode(3); 
		//lc.getStrip(1)->setMode(2);
		//lc.getStrip(2)->setMode(2);
		//lc.getStrip(3)->setMode(2);
		//lc.getStrip(4)->setMode(2);
		//lc.getStrip(5)->setMode(2);
		//prvni.setCRGB(20,20,0);
		//lc.getStrip(0)->setCRGB(255, 255, 0);
		//druhy.setMode(2);
		//lc.getStrip(1)->setCRGB(20, 0, 20);
		counter++;
		//delay(1);
		//druhy.setMode(1);
	}
	
	//delay(1);
	lc.loop();

	//puvodni volani network loopu
	//nc.loop();
	
	//Pri zprovozneni scheduleru
	//yield();
}

/*
void loop2(){

yield();
}
*/