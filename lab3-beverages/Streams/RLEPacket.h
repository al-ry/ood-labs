#pragma once
#include <cstdint>

const int MAX_PACK = 0xFF;

struct Packet
{
	uint8_t bytesCounter = 0;
	uint8_t dataByte = 0;
};