#include "EEPROM.h"



EEPROM::EEPROM(uint8_t IDaddress)
{
	this->IDaddress = IDaddress;
	Wire.begin();
}


EEPROM::~EEPROM()
{
}

void EEPROM::WriteByte(uint16_t address, uint8_t data)
{
	Wire.beginTransmission(address);
	Wire.write(address >> 8);
	Wire.write(address & 0xFF);
	Wire.write(data);
	Wire.endTransmission();
	delay(20);
}

void EEPROM::WriteData(uint16_t address, uint8_t * bytes)
{


}
