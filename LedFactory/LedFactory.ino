#pragma once 
#pragma GCC optimize ("O0")

#include "HF.h"
#include "NetworkCommunication.h"
#include <Adafruit_NeoPixel.h>

HF prvni = HF(1000, 6, NEO_GRB + NEO_KHZ800);
HF druhy = HF(1000, 2, NEO_GRB + NEO_KHZ800);
HF treti = HF(1060, 1, NEO_GRB + NEO_KHZ800);
HF ctvrty = HF(1060, 3, NEO_GRB + NEO_KHZ800);
HF paty = HF(1060, 4, NEO_GRB + NEO_KHZ800);
HF sesty = HF(1060, 5, NEO_GRB + NEO_KHZ800);
uint32_t counter = 0;

uint8_t mac[6] = { 0x00,0x01,0x02,0x03,0x04,0x05 };
IPAddress ip = IPAddress(10, 0, 0, 34);
NetworkCommunication nc = NetworkCommunication(ip, mac);

void setup() {
	// put your setup code here, to run once:

	prvni = HF(1000, 6, NEO_GRB + NEO_KHZ800);
	druhy = HF(1000, 2, NEO_GRB + NEO_KHZ800);
	treti = HF(1060, 1, NEO_GRB + NEO_KHZ800);
	ctvrty = HF(1060, 3, NEO_GRB + NEO_KHZ800);
	paty = HF(1060, 4, NEO_GRB + NEO_KHZ800);
	sesty = HF(1060, 5, NEO_GRB + NEO_KHZ800);

	druhy.blinkColor(255, 0, 0, 0, 0, 255);
}

void loop() {
	// put your main code here, to run repeatedly:

	if (millis() % 100 == 1) {
		druhy.loop();
		prvni.loop();
		treti.loop();
		ctvrty.loop();
		paty.loop();
		sesty.loop();
	}
	//delay(10);
	//Vykresli pásky, zakaž pøerušení
	//noInterrupts();
	if (millis() % 100 == 1) {
	druhy.showIt();
	prvni.showIt();
	treti.showIt();
	ctvrty.showIt();
	paty.showIt();
	sesty.showIt();
		}
	//interrupts();

	if (millis()>20000) {
		prvni.setMode(3);
		//delay(1);
		//druhy.setMode(3);
	}


	//nc.loop();

}
