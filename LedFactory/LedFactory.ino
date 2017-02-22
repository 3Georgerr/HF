//#pragma once 
//#pragma GCC optimize ("O0")


#include "HF.h"
#include "NetworkCommunication.h"
#include <Adafruit_NeoPixel.h>
#include "LedController.h"
//#include <Scheduler.h>

HF prvni = HF(90, 6, NEO_GRB + NEO_KHZ800);
HF druhy = HF(1090, 2, NEO_GRB + NEO_KHZ800);
HF treti = HF(360, 1, NEO_GRB + NEO_KHZ800);
HF ctvrty = HF(360, 3, NEO_GRB + NEO_KHZ800);
HF paty = HF(1240, 4, NEO_GRB + NEO_KHZ800);
HF sesty = HF(1240, 5, NEO_GRB + NEO_KHZ800);
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

	//Scheduler.startLoop(loop2);
}

void loop() {

	//showIT vyraznì zpomaluje
	if (lastTime+interval < millis()) {
		lastTime = millis();
		prvni.loop();
		druhy.loop();
		treti.loop();
		ctvrty.loop();
		prvni.showIt();
		druhy.showIt();
		treti.showIt();
		ctvrty.showIt();
		//	paty.loop();
		//	sesty.loop();
	}
	
	
	if (millis()%10000==1 &&  counter==0) {
		//prvni.setMode(2);
		lc.getStrip(1)->setMode(3); 
		//lc.getStrip(1)->setMode(2);
		//lc.getStrip(2)->setMode(2);
		//lc.getStrip(3)->setMode(2);
		//lc.getStrip(4)->setMode(2);
		//lc.getStrip(5)->setMode(2);
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
	//Pri zprovozneni scheduleru
	//yield();
}

/*
void loop2(){

yield();
}
*/