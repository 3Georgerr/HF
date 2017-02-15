#pragma once 
#pragma GCC optimize ("O0")

#include "HF.h"
//#include "NetworkCommunication.h"
#include <Adafruit_NeoPixel.h>

#include <SPI.h>
#include <UIPEthernet.h>

EthernetServer server = EthernetServer(1000);

HF prvni = HF(1000, 6, NEO_GRB + NEO_KHZ800);
HF druhy = HF(1000, 2, NEO_GRB + NEO_KHZ800);
HF treti = HF(1060, 1, NEO_GRB + NEO_KHZ800);
HF ctvrty = HF(1060, 3, NEO_GRB + NEO_KHZ800);
HF paty = HF(1060, 4, NEO_GRB + NEO_KHZ800);
HF sesty = HF(1060, 5, NEO_GRB + NEO_KHZ800);
uint32_t counter = 0;

//uint8_t mac[6] = { 0x00,0x01,0x02,0x03,0x04,0x05 };
//IPAddress ip = IPAddress(10, 0, 0, 34);
//NetworkCommunication nc = NetworkCommunication(ip, mac);


void setup() {
	// put your setup code here, to run once:
	Serial.begin(9600);
	Serial.println("Test");
	prvni = HF(1000, 6, NEO_GRB + NEO_KHZ800);
	druhy = HF(1000, 2, NEO_GRB + NEO_KHZ800);
	treti = HF(1060, 1, NEO_GRB + NEO_KHZ800);
	ctvrty = HF(1060, 3, NEO_GRB + NEO_KHZ800);
	paty = HF(1060, 4, NEO_GRB + NEO_KHZ800);
	sesty = HF(1060, 5, NEO_GRB + NEO_KHZ800);

	uint8_t mac[6] = { 0x00,0x01,0x02,0x03,0x04,0x05 };
	IPAddress myIP(10, 0, 0, 34);

	Ethernet.begin(mac, myIP);

	server.begin();

	druhy.blinkColor(255, 0, 0, 0, 0, 255);
}

void loop() {
	// put your main code here, to run repeatedly:


	size_t size;

	if (EthernetClient client = server.available())
	{
		while ((size = client.available()) > 0)
		{
			uint8_t* msg = (uint8_t*)malloc(size);
			size = client.read(msg, size);
			Serial.write(msg, size);
			free(msg);
		}
		client.println("DATA from Server!");
		client.stop();
	}

	if (millis() % 100 == 1) {
		druhy.loop();
		prvni.loop();
		treti.loop();
		ctvrty.loop();
		paty.loop();
		sesty.loop();
	}
	//delay(10);
	//Vykresli p�sky, zaka� p�eru�en�
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
