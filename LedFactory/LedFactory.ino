//#pragma once 
//#pragma GCC optimize ("O0")



#include <AT24CX.h>
#include "HF.h"
#include "NetworkCommunication.h"
//#include <Adafruit_NeoPixel.h>
#include <DmxSimple.h>
#include <FastLED\FastLED.h>
//#include "LedController.h"
//#include <Scheduler.h>
#include "Configuration.h"

//SD karta
#include <SPI.h>
#include <SD.h>

#define DEBUG
#define DEBUGNETWORK

//Delka pasku
#define NUMLEDFIRST 1024
#define NUMLEDSECOND 1024
#define NUMLEDTHIRD 1024
#define NUMLEDFOURTH 1024
#define NUMLEDFIFTH 1024
#define NUMLEDSIXTH 1024

//Piny jednotlivych pasku
#define PINSTRIPONE 2
#define PINSTRIPTWO 3
#define PINSTRIPTHREE 4
#define PINSTRIPFOUR 5
#define PINSTRIPFIVE 6
#define PINSTRIPSIX 7



//Tridy Led pasku
HF *prvni;
// = HF(0, PINSTRIPONE);
HF *druhy;
// = HF(0, PINSTRIPTWO);
HF *treti;
// = HF(0, PINSTRIPTHREE);
HF *ctvrty;
// = HF(0, PINSTRIPFOUR);
HF *paty;
// = HF(0, PINSTRIPFIVE);
HF *sesty;
// = HF(0, PINSTRIPSIX);

//nastaveni sitovych parametru (mac,ip)
uint8_t mac[6] = { 0x00,0x01,0x02,0x03,0x04,0x05 };
IPAddress ip = IPAddress(10, 0, 0, 34);
IPAddress myNetmask = IPAddress(255,255,255,0);
IPAddress  myGateway = IPAddress(10, 0, 0, 138);
IPAddress myDNS = IPAddress(8,8,8,8);
NetworkCommunication nc = NetworkCommunication(6,mac, ip,myDNS,myGateway,myNetmask);

//Led controller ovlada pasky pomoci dat ze site
//LedController lc = LedController(6);


uint32_t counter = 0;
uint32_t interval = 100;
uint32_t lastTime = 0;


void setup() {

	counter = 0;
	interval = 100;
	lastTime = 0;

	pinMode(PINSTRIPONE, OUTPUT);
	pinMode(PINSTRIPTWO, OUTPUT);
	pinMode(PINSTRIPTHREE, OUTPUT);
	pinMode(PINSTRIPFOUR, OUTPUT);
	pinMode(PINSTRIPFIVE, OUTPUT);
	pinMode(PINSTRIPSIX, OUTPUT);

	digitalWrite(PINSTRIPONE, LOW);
	digitalWrite(PINSTRIPTWO, LOW);
	digitalWrite(PINSTRIPTHREE, LOW);
	digitalWrite(PINSTRIPFOUR, LOW);
	digitalWrite(PINSTRIPFIVE, LOW);
	digitalWrite(PINSTRIPSIX, LOW);

#ifdef DEBUG
	Serial.begin(9600);
	while (!Serial) {
		; //wait for serial port to connect. Needed for native USB port only.
	}
	//Serial.print("test");
	//Serial.flush();
#endif

	Configuration config;
	config.initialize();

	bool dataZSD = config.ReadFromSDCard("config.txt");

#ifdef DEBUG
	Serial.print("Soubor na SD dostupny:");
	Serial.println(dataZSD);
	Serial.println(" ");
	Serial.flush();
#endif // DEBUG

#ifdef DEBUG
	for (int i = 0; i < 6; i++) {
		Serial.println(config.getNumOfLed(i));
	}
	Serial.println(" ");
	Serial.flush();
#endif // DEBUG

	///*
	prvni = new HF(config.getNumOfLed(0), PINSTRIPONE);
	druhy = new HF(config.getNumOfLed(1), PINSTRIPTWO);
	treti = new HF(config.getNumOfLed(2), PINSTRIPTHREE);
	ctvrty = new HF(config.getNumOfLed(3), PINSTRIPFOUR);
	paty = new HF(config.getNumOfLed(4), PINSTRIPFIVE);
	sesty = new HF(config.getNumOfLed(5), PINSTRIPSIX);
	//*/

	//Pridame pasky k vykresleni

	CRGB test;

	FastLED.addLeds<DMXSIMPLE, 2, RGB>(test, 1);
	FastLED.addLeds<WS2812B, PINSTRIPONE, GRB>(prvni->getLedArray(), config.getNumOfLed(0));
	FastLED.addLeds<WS2812B, PINSTRIPTWO, GRB>(druhy->getLedArray(), config.getNumOfLed(1));
	FastLED.addLeds<WS2812B, PINSTRIPTHREE, GRB>(treti->getLedArray(), config.getNumOfLed(2));
	FastLED.addLeds<WS2812B, PINSTRIPFOUR, GRB>(ctvrty->getLedArray(), config.getNumOfLed(3));
	FastLED.addLeds<WS2812B, PINSTRIPFIVE, GRB>(paty->getLedArray(), config.getNumOfLed(4));
	FastLED.addLeds<WS2812B, PINSTRIPSIX, GRB>(sesty->getLedArray(), config.getNumOfLed(5));


	//	ip = IPAddress(10, 0, 0, 34);

		//Funguje
	ip = config.getIP();
	myDNS = config.getDNS();
	myGateway = config.getGateway();
	myNetmask = config.getNetmask();
	config.getMAC(mac);
	//delay(100);

#ifdef DEBUGNETWORK
	Serial.print("IP:");
	Serial.print(ip[0]);
	Serial.print(".");
	Serial.print(ip[1]);
	Serial.print(".");
	Serial.print(ip[2]);
	Serial.print(".");
	Serial.println(ip[3]);

	Serial.print("Netmask:");
	Serial.print(myNetmask[0]);
	Serial.print(".");
	Serial.print(myNetmask[1]);
	Serial.print(".");
	Serial.print(myNetmask[2]);
	Serial.print(".");
	Serial.println(myNetmask[3]);

	Serial.print("Gateway:");
	Serial.print(myGateway[0]);
	Serial.print(".");
	Serial.print(myGateway[1]);
	Serial.print(".");
	Serial.print(myGateway[2]);
	Serial.print(".");
	Serial.println(myGateway[3]);

	Serial.print("DNS:");
	Serial.print(myDNS[0]);
	Serial.print(".");
	Serial.print(myDNS[1]);
	Serial.print(".");
	Serial.print(myDNS[2]);
	Serial.print(".");
	Serial.println(myDNS[3]);

	Serial.print("MAC:");
	Serial.print(mac[0]);
	Serial.print(".");
	Serial.print(mac[1]);
	Serial.print(".");
	Serial.print(mac[2]);
	Serial.print(".");
	Serial.print(mac[3]);
	Serial.print(".");
	Serial.print(mac[4]);
	Serial.print(".");
	Serial.println(mac[5]);
	Serial.flush();
#endif

	nc = NetworkCommunication(6, mac, ip, myDNS, myGateway, myNetmask);

	//Prevod LedControlleru na NetworkCommunication
	nc.setStrip(prvni, 0);
	nc.setStrip(druhy, 1);
	nc.setStrip(treti, 2);
	nc.setStrip(ctvrty, 3);
	nc.setStrip(paty, 4);
	nc.setStrip(sesty, 5);

	nc.setConfig(&config);

	//predame odkaz na led pasky a network "driver"
	/*
	lc.setStrip(prvni, 0);
	lc.setStrip(druhy, 1);
	lc.setStrip(treti, 2);
	lc.setStrip(ctvrty, 3);
	lc.setStrip(paty, 4);
	lc.setStrip(sesty, 5);
	lc.setNetworkcommunication(nc);
	*/

	//lc.getStrip(0)->blinkColor(0, 10, 1, 0, 1, 1);
	//lc.getStrip(0)->blinkCRGB(0, 0, 1, 0, 1, 0);
	//lc.getStrip(1)->blinkColor(1, 0, 0, 0, 0, 1);
	
	nc.start();

	//Scheduler.startLoop(loop2);
}

void loop() {

	if (lastTime + interval < millis()) {
		lastTime = millis();
		FastLED.show();
	}

	//lc.loop();
	nc.loop();


	//Testovani
	/*if (millis()>10000 == 1 && counter == 0) {
		lc.getStrip(0)->setMode(0);
		lc.getStrip(1)->setMode(0);
		lc.getStrip(2)->setMode(0);
	}
	*/

	/*
	//nyni probiha v hlavni smycce ledControlleru
	lc.getStrip(0)->loop();
	lc.getStrip(1)->loop();
	lc.getStrip(2)->loop();
	lc.getStrip(3)->loop();
	lc.getStrip(4)->loop();
	lc.getStrip(5)->loop();
	*/
	
	/*
		//prvni.setMode(2);
		//lc.getStrip(1)->setMode(3); 
		lc.getStrip(1)->setMode(3);
		lc.getStrip(0)->setMode(2);
		//lc.getStrip(3)->setMode(2);
		//lc.getStrip(4)->setMode(2);
		//lc.getStrip(5)->setMode(2);
		//prvni.setColor(20,20,0);
		//lc.getStrip(0)->setCRGB(255, 255, 0);
		//druhy.setMode(2);
		//lc.getStrip(1)->setCRGB(20, 0, 20);
		counter++;
		//delay(1);
		//druhy.setMode(1);
	}
	*/

	
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

