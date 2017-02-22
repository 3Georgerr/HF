//#pragma once 
//#pragma GCC optimize ("O0")


#include "HF.h"
#include "NetworkCommunication.h"
#include <Adafruit_NeoPixel.h>
#include "LedController.h"
#include <Scheduler.h>

HF prvni = HF(1090, 6, NEO_GRB + NEO_KHZ800);
HF druhy = HF(1090, 2, NEO_GRB + NEO_KHZ800);
HF treti = HF(1240, 1, NEO_GRB + NEO_KHZ800);
HF ctvrty = HF(1240, 3, NEO_GRB + NEO_KHZ800);
HF paty = HF(1240, 4, NEO_GRB + NEO_KHZ800);
HF sesty = HF(1240, 5, NEO_GRB + NEO_KHZ800);
uint32_t counter = 0;

uint8_t mac[6] = { 0x00,0x01,0x02,0x03,0x04,0x05 };
IPAddress ip = IPAddress(10, 0, 0, 34);
NetworkCommunication nc = NetworkCommunication(mac, ip);
LedController lc = LedController(6);

void setup() {
	// put your setup code here, to run once:
	
	//Pro testování funkcí, neøešíme èasování
	/*
	prvni = HF(60, 6, NEO_GRB + NEO_KHZ800);
	druhy = HF(90, 2, NEO_GRB + NEO_KHZ800);
	treti = HF(40, 1, NEO_GRB + NEO_KHZ800);
	ctvrty = HF(40, 3, NEO_GRB + NEO_KHZ800);
	paty = HF(40, 4, NEO_GRB + NEO_KHZ800);
	sesty = HF(40, 5, NEO_GRB + NEO_KHZ800);
	*/

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
	//lc.getStrip(0)->blinkColor(0, 0, 1, 0, 1, 0);
	//lc.getStrip(1)->blinkColor(1, 0, 0, 0, 0, 1);
	
	//prvni.blinkColor(0, 1, 1, 1, 1, 1);
	//prvni.blinkColor(0, 10, 1, 0, 1, 1);
	//prvni.blinkColor(0, 0, 255);
	//druhy.blinkColor(1, 0, 0, 0, 1, 0);
	//prvni.blinkColor(0, 0, 255, 0, 255, 0);

	nc.start();

	Scheduler.startLoop(loop2);
}

void loop() {
	uint32_t test = millis();
	//delay(10);
	//Vykresli pásky, zakaž pøerušení
	//noInterrupts();
	if (test % 100 == 1) {
		druhy.showIt();
		prvni.showIt();
		treti.showIt();
		ctvrty.showIt();
		paty.showIt();
		sesty.showIt();
	}
	//interrupts();
	//lc.getStrip(0)->setMode(1);
	
	if (millis()%10000==1) {
		//prvni.setMode(2);
		lc.getStrip(0)->setMode(2); 
		lc.getStrip(1)->setMode(2);
		lc.getStrip(2)->setMode(2);
		lc.getStrip(3)->setMode(2);
		lc.getStrip(4)->setMode(2);
		lc.getStrip(5)->setMode(2);
		//prvni.setColor(20,20,0);
		//lc.getStrip(0)->setColor(255, 255, 0);
		//druhy.setMode(2);
		//lc.getStrip(1)->setColor(20, 0, 20);
		counter++;
		//delay(1);
		//druhy.setMode(1);
	}
	
	//delay(1);
	lc.loop();

	//puvodni volani network loopu
	//nc.loop();
	yield();
}

void loop2(){

uint32_t test = millis();
if (test % 100 == 1) {
	druhy.loop();
	prvni.loop();
	treti.loop();
	ctvrty.loop();
	paty.loop();
	sesty.loop();
}
yield();
}