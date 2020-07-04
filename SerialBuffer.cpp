
/*

	SERIAL BUFFER FUNCTIONS
	ARDUINO & STM32
    LAST UPDATE: 21. 4. 2020.
    CREDITS: Nick Gammon & Pararera (c)

*/


// MODULES
#include 																			"SerialBuffer.h"

// LIBRARIES
#include 																			<Arduino.h>



// OBJECT CONSTRUCTORS
SBuff::SBuff()
{
	buffedBytes = new char [SERIAL_BUFFER + 1]; // + 1 FOR \0 SIGN
	if (buffedBytes != nullptr) // SUCCESS
	{
		allocFail = false;
		buffAlloc = SERIAL_BUFFER;
		memset(buffedBytes, '\0', SERIAL_BUFFER);
	}
	buffIdx = 0;
	allocFail = false;
	buffAlloc = 256;
	buffIdx = 0;
}

SBuff::SBuff(uint16_t const size)
{
	buffedBytes = new char [size + 1]; // + 1 FOR \0 SIGN
	if (buffedBytes != nullptr) // SUCCESS
	{
		allocFail = false;
		buffAlloc = size;
		memset(buffedBytes, '\0', size);
	}
	buffIdx = 0;
}


// OBJECT DECONSTRUCTOR
SBuff::~SBuff()
{
	if (!allocFail) delete [] buffedBytes;
}


// MAIN BUFFER FUNCTION
int8_t SBuff::buff(uint8_t const incomingByte)
{
	if (!allocFail)
	{
		switch (incomingByte)
		{
			case '\n':
			{
				buffedBytes[buffIdx] = '\0';
				return (BUFF_END);
			}

			case '\r': return (BUFF_CONTINUE);

			default:
			{
				// OVERFLOW PROTECTION
				if (buffIdx < buffAlloc)
				{
					buffedBytes[buffIdx++] = incomingByte;
					lastBuffMillis = millis();
				}
				else return (BUFF_OVERFLOW);
				return (BUFF_CONTINUE);
			}
		}	
	}
	else return (BUFF_ALLOC_FAIL);
}

// BUFFER FUNCTIONS
void SBuff::buff(uint8_t const incomingByte, void (*func)())
{
	if (buff(incomingByte) == BUFF_END)
	{
		func();
		dump();
	}
}

void SBuff::buff(uint8_t const incomingByte, void (*func)(), bool const ofCall)
{
	int8_t value = buff(incomingByte);
	if (value == BUFF_END || value == BUFF_OVERFLOW)
	{
		func();
		dump();
	}
}

char *SBuff::buffer() const
{
	return (buffedBytes);
}

// END FUNCTION
uint16_t SBuff::end(void (*func)())
{
	if (buffIdx != 0)
	{
		func();
		return (dump());
	}
	else return (0);
}

// DUMP FUNCTION
uint16_t SBuff::dump()
{
	if (!allocFail)
	{
		uint16_t dumped = buffIdx - 1; // - 1 TO EXCLUDE NULL BYTE AT THE END
		buffIdx = 0;
		memset(buffedBytes, '\0', buffAlloc);
		return (dumped);
	}
	else return (0);	
}

// GET BUFFED SIZE
uint16_t SBuff::buffed() const
{
	return (buffIdx);
}

// GET ALLOCATED SIZE
uint16_t SBuff::size() const
{
	return (buffAlloc);
}

// MEMORY STATUS
bool SBuff::isFail() const
{
	return (allocFail);
}

// LAST BUFF
uint32_t SBuff::lastBuff() const
{
	return (lastBuffMillis);
}