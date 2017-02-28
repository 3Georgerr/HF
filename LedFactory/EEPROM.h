#pragma once
#ifndef _EEPROM_h
#define _EEPROM_h
#include <Wire.h>
#endif
class EEPROM
{
	byte IDaddress;

public:
	EEPROM(byte address);
	~EEPROM();
	
	void WriteByte(uint16_t address,uint8_t byte);
	void WriteData(uint16_t address,uint8_t *bytes );

};

