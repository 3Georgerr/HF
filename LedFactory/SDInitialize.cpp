#include "SDInitialize.h"

IPAddress SDInitialize::ip= IPAddress(192, 168, 10, 10);
uint8_t SDInitialize::macAddress[6] = { 0x00,0x01,0x02,0x03,0x04,0x05 };

uint16_t SDInitialize::numLedFirst=1024;
uint16_t SDInitialize::numLedSecond=1024;
uint16_t SDInitialize::numLedThird=1024;
uint16_t SDInitialize::numLedFourth=1024;
uint16_t SDInitialize::numLedFifth=1024;
uint16_t SDInitialize::numLedSixth=1024;


void SDInitialize::initialize()
{


}

SDInitialize::SDInitialize()
{
}


SDInitialize::~SDInitialize()
{
}
