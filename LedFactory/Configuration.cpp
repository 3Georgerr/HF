#include "Configuration.h"

void Configuration::initialize(uint8_t eepromAddress)
{
	eeprom= AT24C32(eepromAddress);

	//Inicializace karty
	if (SD.begin(CSPINSDCARD)) {
		sdAvailable = true;
	}
}

void Configuration::setParameters(char array[4][31],uint8_t NumOfparams=4)
{
	if (strcmp(array[0], "strip")) {
		setStrip(array + 1, NumOfparams);
		writeNumOfLedsToEEPROM(atoi(array[1]));
		}
		else if (strcmp(array[0], "ip")) {
			setIP(array[1]);
			writeIPToEEPROM();
		}
		else if (strcmp(array[0], "subnet")) {
			setSubnet(array[1]);
			writeIPToEEPROM(4);
		}
		else if (strcmp(array[0], "gateway")) {
			setGateway(array[1]);
			writeIPToEEPROM(8);
		}
		else if (strcmp(array[0], "dns")) {
			setDNS(array[1]);
			writeIPToEEPROM(12);
		}
		else if (strcmp(array[0], "mac")) {
			setMac(array[1]);
			writeMACToEEPROM();
		}
}


void Configuration::setStrip(char array[3][31], uint8_t NumOfparams) {
	uint8_t strip;
	uint16_t num;

	Serial.println("hodnoty");
	Serial.println(array[0]);
	Serial.println(array[1]);
	Serial.println(array[2]);

	strip = atoi(array[0])-1;
	num = atoi(array[1]);
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
void Configuration::setSubnet(char* array) {
	int values[6];
	int i;
	if (6 == sscanf(array, "%d.%d.%d.%d%c",
		&values[0], &values[1], &values[2],
		&values[3]))
	{
		/* convert to uint8_t */
		for (i = 0; i < 4; ++i)
			this->subnet[i] = (uint8_t)values[i];
	}
}
void Configuration::setGateway(char* array) {
	int values[6];
	int i;
	if (6 == sscanf(array, "%d.%d.%d.%d%c",
		&values[0], &values[1], &values[2],
		&values[3]))
	{
		/* convert to uint8_t */
		for (i = 0; i < 4; ++i)
			this->gateway[i] = (uint8_t)values[i];
	}
}
void Configuration::setDNS(char* array) {
	int values[6];
	int i;
	if (6 == sscanf(array, "%d.%d.%d.%d%c",
		&values[0], &values[1], &values[2],
		&values[3]))
	{
		/* convert to uint8_t */
		for (i = 0; i < 4; ++i)
			this->dns[i] = (uint8_t)values[i];
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
	char line[31];
	char * temp;
	char chars_array[4][31];

	//	line = new char[31];

	sdConfiguration = SD.open(file);
	if (sdConfiguration) {
		// read from the file until there's nothing else in it:
		i = 0;
		while (sdConfiguration.available()) {
			i = sdConfiguration.readBytesUntil('\n', line, 30);
			line[i] = '\0';
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
				temp = strtok(NULL, "=");
			}

			//Zpracuj data
			setParameters(chars_array, 4);

			chars_array[0][0] = '\0';
			chars_array[1][0] = '\0';
			chars_array[2][0] = '\0';
			chars_array[3][0] = '\0';
		}
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
	return this->ip;
}
IPAddress Configuration::getSubnet()
{
	return this->subnet;
}
IPAddress Configuration::getGateway()
{
	return this->gateway;
}
IPAddress Configuration::getDNS()
{
	return this->dns;
}
void Configuration::getMAC(uint8_t mac[])
{
	for (int i = 0; i < 6; i++) {
		mac[i] = macAddress[i];
	}

}
int Configuration::getNumOfLed(uint8_t strip)
{
	return numLed[strip];
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
void Configuration::writeNumOfLedsToEEPROM(uint8_t strip,uint16_t offset) {
	eeprom.write((strip - 1) * 2 + 0 + offset, numLed[strip-1] & 0xff);
	eeprom.write((strip - 1) * 2 + 1 + offset, numLed[strip-1] >> 8 );
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
void Configuration::readNumOfLedsFromEEPROM(uint8_t strip, uint16_t offset) {
	byte low;
	byte high;
	low = 0x00;
	high = 0x00;
	low = eeprom.read((strip - 1) * 2 + 0 + offset);
	high = eeprom.read((strip - 1) * 2 + 1 + offset);
	numLed[strip - 1] = (high << 8) + low;
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
	subnet = IPAddress(255, 255, 255, 0);
	gateway = IPAddress(10, 0, 0, 138);
	dns = IPAddress(8, 8, 8, 8);

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
