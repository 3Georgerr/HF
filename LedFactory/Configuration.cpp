#include "Configuration.h"


IPAddress Configuration::ip = IPAddress(192, 168, 10, 10);
uint8_t Configuration::macAddress[6] = { 0x00,0x01,0x02,0x03,0x04,0x05 };

uint16_t Configuration::numLedFirst = 1024;
uint16_t Configuration::numLedSecond = 1024;
uint16_t Configuration::numLedThird = 1024;
uint16_t Configuration::numLedFourth = 1024;
uint16_t Configuration::numLedFifth = 1024;
uint16_t Configuration::numLedSixth = 1024;


void Configuration::initialize()
{
	AT24C32 eeprom(7);
	byte IPAddress[4];
	IPAddress[0] = eeprom.read(0);
	IPAddress[1] = eeprom.read(1);
	IPAddress[2] = eeprom.read(2);
	IPAddress[3] = eeprom.read(3);
	ip = (IPAddress);
	Serial.print("IP ulozena v EEPROM ");
	Serial.print(IPAddress[0]);
}

Configuration::Configuration()
{
}


Configuration::~Configuration()
{
}
