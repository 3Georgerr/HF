//#pragma once 
//#pragma GCC optimize ("O0")



#include <AT24CX.h>
#include "HF.h"
#include "NetworkCommunication.h"
//#include <Adafruit_NeoPixel.h>
#include <FastLED\FastLED.h>
#include "LedController.h"
//#include <Scheduler.h>
#include "Configuration.h"

//SD karta
#include <SPI.h>
#include <SD.h>

#define DEBUG

//Delka pasku
#define NUMLEDFIRST 1024
#define NUMLEDSECOND 1024
#define NUMLEDTHIRD 1024
#define NUMLEDFOURTH 1024
#define NUMLEDFIFTH 1024
#define NUMLEDSIXTH 1024

//Piny jednotlivych pasku
#define PINSTRIPONE 1
#define PINSTRIPTWO 6
#define PINSTRIPTHREE 2
#define PINSTRIPFOUR 4
#define PINSTRIPFIVE 5
#define PINSTRIPSIX 7


//String a = "WS2812B";

//Tridy Led pasku
HF prvni = HF(NUMLEDFIRST, PINSTRIPONE);
HF druhy = HF(NUMLEDSECOND, PINSTRIPTWO);
HF treti = HF(NUMLEDTHIRD, PINSTRIPTHREE);
HF ctvrty = HF(NUMLEDFOURTH, PINSTRIPFOUR);
HF paty = HF(NUMLEDFIFTH, PINSTRIPFIVE);
HF sesty = HF(NUMLEDSIXTH, PINSTRIPSIX);


//nastaveni sitovych parametru (mac,ip)
uint8_t mac[6] = { 0x00,0x01,0x02,0x03,0x04,0x05 };
IPAddress ip = IPAddress(10, 0, 0, 34);
NetworkCommunication nc = NetworkCommunication(mac, ip);
//Led controller ovlada pasky pomoci dat ze site
LedController lc = LedController(6);


uint32_t counter = 0;
uint32_t interval = 100;
uint32_t lastTime = 0;



void setup() {

	counter = 0;
	interval = 100;
	lastTime = 0;

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

	Serial.print("Soubor na SD dostupny:");
	Serial.println(dataZSD);
	Serial.println(" ");
	Serial.flush();
	//config.setIP();




	///*
	prvni = HF(NUMLEDFIRST, PINSTRIPONE);
	druhy = HF(NUMLEDSECOND, PINSTRIPTWO);
	treti = HF(NUMLEDTHIRD, PINSTRIPTHREE);
	ctvrty = HF(NUMLEDFOURTH, PINSTRIPFOUR);
	paty = HF(NUMLEDFIFTH, PINSTRIPFIVE);
	sesty = HF(NUMLEDSIXTH, PINSTRIPSIX);
	//*/

	//Pridame pasky k vykresleni
	FastLED.addLeds<WS2812B, PINSTRIPONE, GRB>(prvni.getLedArray(), NUMLEDFIRST);
	FastLED.addLeds<WS2812B, PINSTRIPTWO, GRB>(druhy.getLedArray(), NUMLEDSECOND);
	FastLED.addLeds<WS2812B, PINSTRIPTHREE, GRB>(treti.getLedArray(), NUMLEDTHIRD);
	FastLED.addLeds<WS2812B, PINSTRIPFOUR, GRB>(ctvrty.getLedArray(), NUMLEDFOURTH);
	FastLED.addLeds<WS2812B, PINSTRIPFIVE, GRB>(paty.getLedArray(), NUMLEDFIFTH);
	FastLED.addLeds<WS2812B, PINSTRIPSIX, GRB>(sesty.getLedArray(), NUMLEDSIXTH);


	ip = IPAddress(10, 0, 0, 34);

	//Funguje
	config.readIPFromEEPROM();
	ip = config.getIP();

	//config.setMAC();
	//config.readMAC();
	config.getMAC(mac);
	delay(100);
	nc = NetworkCommunication(mac, ip);
	

	//predame odkaz na led pasky a network "driver"
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
	lc.getStrip(0)->setMode(4);
	
	nc.start();

	//Scheduler.startLoop(loop2);
}

void loop() {

	if (lastTime + interval < millis()) {
		lastTime = millis();
		FastLED.show();
	}

	lc.loop();

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