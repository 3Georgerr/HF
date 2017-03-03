#include "Configuration.h"

void Configuration::initialize(uint8_t eepromAddress)
{
	eeprom= AT24C32(eepromAddress);

	//Inicializace karty
	if (SD.begin(CSPINSDCARD)) {
		sdAvailable = true;
	}
}

void Configuration::setParameters(char ** array, uint8_t size,uint8_t NumOfparams=4)
{
		if (strcmp(array[0], "strip")) {
			setStrip(array,NumOfparams);
		}
		else if (strcmp(array[0], "ip")) {
			setIP(array[1]);
		}
		else if (strcmp(array[0], "mac")) {
			setMac(array[1]);
		}
}

void Configuration::setStrip(char** array,uint8_t NumOfparams) {
	uint8_t strip;
	uint16_t num;

	strip = atoi(array[1])-1;
	num = atoi(array[2]);
	if (strip <= numOfStrips) {
		numLed[strip] = num;
	}
}

void Configuration::setIP(char* array) {
	int values[6];
	int i;
	if (6 == sscanf(array, "%d.%d.%d.%d%c",
		&values[0], &values[1], &values[2],
		&values[3]))
	{
		/* convert to uint8_t */
		for (i = 0; i < 4; ++i)
			this->ip[i] = (uint8_t)values[i];
	}
}

void Configuration::setMac(char* array) {
	int values[6];
	int i;

	if (6 == sscanf(array, "%x:%x:%x:%x:%x:%x%c",
		&values[0], &values[1], &values[2],
		&values[3], &values[4], &values[5]))
	{
		/* convert to uint8_t */
		for (i = 0; i < 6; ++i)
			macAddress[i] = (uint8_t)values[i];
	}

	else
	{
		/* invalid mac */
	}
}


bool Configuration::ReadFromSDCard(char * file="config.txt")
{
	int i,p;
	char * line;
	char * temp;
	char chars_array[4][31];

	line = new char[31];

	sdConfiguration = SD.open(file);
	if (sdConfiguration) {
		// read from the file until there's nothing else in it:
		i = 0;
		while (sdConfiguration.available()) {
			i = sdConfiguration.readBytesUntil('\n', line, 30);
			line[i - 1] = '\0';
			p = 0;
			Serial.println(line);
			chars_array[0][0] = '\0';
			chars_array[1][0] = '\0';
			chars_array[2][0] = '\0';
			chars_array[3][0] = '\0';
			temp = strtok(line, "=");

			while (temp) {
				strncpy(chars_array[p], temp, 30);
				chars_array[p++][31] = '\0';
				Serial.println(temp);
				temp = strtok(NULL, "=");
			}

			Serial.print("O ");
			Serial.println(chars_array[0]);
			Serial.print("1 ");
			Serial.println(chars_array[1]);
			Serial.print("2 ");
			Serial.println(chars_array[2]);
			Serial.print("3 ");
			Serial.println(chars_array[3]);
			Serial.flush();

			chars_array[0][0] = '\0';
			chars_array[1][0] = '\0';
			chars_array[2][0] = '\0';
			chars_array[3][0] = '\0';

		}
		delete line;
		// close the file:
		sdConfiguration.close();
		return true;
	}
	else{
	}
	//Can´t open file
	return false;
}


IPAddress Configuration::getIP()
{
	return ip;
}
void Configuration::getMAC(uint8_t mac[])
{
	for (int i = 0; i < 6; i++) {
		mac[i] = macAddress[i];
	}

}

void Configuration::writeIPToEEPROM(uint16_t offset)
{
	eeprom.write(0 + offset,ip[0]);
	eeprom.write(1 + offset, ip[1]);
	eeprom.write(2 + offset, ip[2]);
	eeprom.write(3 + offset, ip[3]);
}
void Configuration::writeMACToEEPROM(uint16_t offset)
{
		eeprom.write(0 + offset, &macAddress[0],6);
}

void Configuration::readIPFromEEPROM(uint16_t offset)
{
	byte IPAddress[4];
	eeprom.read(0 + offset, IPAddress, 4);
	ip = (IPAddress);
}
void Configuration::readMACFromEEPROM(uint16_t offset)
{
	eeprom.read(0 + offset,macAddress,6);
}

Configuration::Configuration()
{
	int i;

	macAddress[0] = 0x00;
	macAddress[1] = 0x10;
	macAddress[2] = 0x02;
	macAddress[3] = 0x03;
	macAddress[4] = 0x04;
	macAddress[5] = 0x05;

	ip = IPAddress(10, 0, 0, 34);

	numOfStrips = NUMOFSTRIPS;
	for (i = 0; i < numOfStrips; i++) {
		numLed[i] = 1024;
	}
	


	sdAvailable = false;
	gotData = false;
}


Configuration::~Configuration()
{
}
