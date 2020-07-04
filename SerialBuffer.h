
/*

	SERIAL BUFFER FUNCTIONS
	ARDUINO & STM32
    LAST UPDATE: 21. 4. 2020.
    CREDITS: Nick Gammon & Pararera (c)

*/


#ifndef _SBUFF_H
#define _SBUFF_H


// MODULES
#include 																			<Arduino.h>


// SETTINGS
/*
	Size of buffer for buffering bytes from Serial
	@values: 32-256 recommended
	@unit: bytes
*/
#ifndef SERIAL_BUFFER
	#define SERIAL_BUFFER															64
#endif


// RETURN CODES
#define BUFF_END	 																1
#define BUFF_CONTINUE 																0
#define BUFF_OVERFLOW 																-1
#define BUFF_ALLOC_FAIL 															-2


// CLASS
class SBuff {
public:
	// ----- OBJECT CONSTRUCOTRS
	SBuff();
	/*
		@params:
			- size: Buffer size
	*/
	SBuff(uint16_t const);

	// ----- OBJECT DECONSTRUCTOR
	~SBuff();
	

	// ----- FUNCTIONS
	/*
		Buffs incoming byte into buffer
		@params:
			- incomingByte: Byte to put into buffer
			- func: Function that will be called after LF sign
	*/
	void buff(uint8_t const, void (*func)());

	/*
		Buffs incoming byte into buffer
		@params:
			- incomingByte: Byte to put into buffer
			- func: Function that will be called after LF sign
			- ofCall: Call "func" in case of the overflow
	*/
	void buff(uint8_t const, void (*func)(), bool const);	

	/*
		Returns memory address of the buffer
		@return:
			- Memory address of the buffer
	*/
	char *buffer() const;	

	/*
		Returns number of buffed bytes from "buff" function
		@return:
			- 16-bit number of buffed bytes
	*/
	uint16_t buffed() const;

	/*
		Returns size of allocated memory in bytes for "buffer"
		@return:
			- 16-bit number of allocated bytes
	*/
	uint16_t size() const;	

	/*
		Ends buffering process
		@params:
			- func: Function that will be called
		@return:
			- 16-bit number of buffed bytes
	*/
	uint16_t end(void (*func)());

	/*
		Dumps all buffed bytes
		@return:
			- 16-bit number of bumped bytes
	*/
	uint16_t dump();

	/*
		Returns is memory allocated properly for buffer
		@return:
			- bool value
	*/
	bool isFail() const;

	/*
		Returns millis of last buffed byte
		@return:
			- Millis of last buffed byte
	*/
	uint32_t lastBuff() const;

private:
	// ----- FUNCTIONS
	/*
		Buffs incoming byte into buffer
		@params:
			- incomingByte: Byte to put into buffer
		@return:
			- 8-bit signed value
	*/
	int8_t buff(uint8_t const);


	// ----- VARIABLES
	uint16_t buffIdx = 0;
	uint16_t buffAlloc = SERIAL_BUFFER;
	bool allocFail = false;
	uint32_t lastBuffMillis = 0;
	char *buffedBytes;
};


#endif // _SBUFF_H