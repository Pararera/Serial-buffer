
/*

	SERIAL BUFFER FUNCTIONS
	ARDUINO & STM32
    LAST UPDATE: 21. 4. 2020.
    CREDITS: NickGammon & Pararera (c)

    TESTED ON BLUEPILL AND ARDUINO NANO BOARDS.
    SENT TEXT HAS TO HAVE LF AT THE END.

*/

#include 																			<SerialBuffer.h>


// SETTINGS
#define BUFF_SIZE 																	256 


// OBJECT
SBuff Buffer(BUFF_SIZE); 


// ECHO FUNCTION
void echo()
{
	Serial.print(F("You wrote: "));
	Serial.println(Buffer.buffer());
	Serial.print('\n');
}


void setup()
{
	delay(100);
	Serial.begin(115200);

	Serial.println(F("\n-->> SERIAL BUFFER EXAMPLE\nStart typing, otherwise you will not hear any echo!"));

	// CHECKS WHAT HAPPEND WITH MEMORY ALLOCATION
	if (Buffer.isFail())
	{
		Serial.println(F("Memory allocation fail!"));
		while (true) delay(1000);
	}
	else
	{
		Serial.print(F("Buffer size: "));
		Serial.println(Buffer.size(), DEC);
	}
}

void loop()
{
	// BUFFS BYTES WHILE THEY ARE AVAILABLE
	while (Serial.available()) Buffer.buff(Serial.read(), &echo, true);
	if (millis() - Buffer.lastBuff() > 999 && Buffer.buffed())
	{
		Serial.print(F("Dumped "));
		Serial.print(Buffer.dump(), DEC);
		Serial.println(F(" bytes"));
	}

	delay(1); // SLOWS DOWN
}