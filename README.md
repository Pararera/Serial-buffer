# SERIAL BUFFER FOR ARDUINO

## ABOUT

This library contains functions for buffering data from <b>Serial</b> communication. The library can handle multiple serial ports at once. See example sketch for better understanding of the library.

<br/><br/>

## INSTALLATION

<ul>
  <li>Download the library</li>
  <li>Extract files using WinRAR(or similar software) to location <i>C:\Users\{YOUR_USERNAME}\Documents\Arduino\libraries</i></li>
</ul>

<br/><br/>

## USING LIBRARY

In your sketch, at the top add `#include <SerialBuffer.h>`. Somewhere below all include files add `SBuff {OBJECT_NAME};` or `SBuff {OBJECT_NAME}({BUFFER_SIZE});`.
Replace `{OBJECT_NAME}` with the name you want. Replace `{BUFFER_SIZE}` with the buffer size you want.
Provide `{BUFFER_SIZE}` to object constructor for custom size buffer, otherwise `SERIAL_BUFFER` bytes will be allocated for the buffer.

<br/><br/>

## SETTINGS

<ul>
  <li><b>SERIAL_BUFFER</b> - If you want to change default size of the buffer, in <i>SerialBuffer.h</i> change <i>SERIAL_BUFFER</i> value with yours. Recommended value is from 32 up to 256 bytes.</li>
</ul>

<br/><br/>

## FUNCTIONS

### void buff(uint8_t const incomingByte, void (*func)(), bool const ofCall)

Handles all buffering job for you. Call it when Serial has available bytes.

<b>Parameters</b>
<ul>
  <li><b>incomingByte</b> - Byte which will be buffed into the buffer</li>
  <li><b>func</b> - The address of the function that will be called at the end of buffering process. Buffering process will end with <i>LF</i> sign.</li>
  <li><b>ofCall</b> (optional) - Set it to <i>true</i> to call <i>func</i> in case of buffer overflow.</li>
</ul>

<b>Return</b>
<ul>
  <li>Nothing</li>
</ul>

<br/>

### char *buffer()

Returns memory address of the buffer. Use it to read from the buffer.

<b>Parameters</b>
<ul>
  <li>None</li>
</ul>

<b>Return</b>
<ul>
  <li>Buffer memory address</li>
</ul>

<br/>

### uint16_t buffed()

Returns number of buffed bytes. 

<b>Parameters</b>
<ul>
  <li>None</li>
</ul>

<b>Return</b>
<ul>
  <li>16-bit value</li>
</ul>

<br/>

### uint16_t size()

Returns number of allocated bytes for the buffer

<b>Parameters</b>
<ul>
  <li>None</li>
</ul>

<b>Return</b>
<ul>
  <li>16-bit value</li>
</ul>

<br/>

### uint16_t end(void (*func)())

Ends buffering process.

<b>Parameters</b>
<ul>
  <li><b>func</b> - The address of the function that will be called.</li>
</ul>

<b>Return</b>
<ul>
  <li>Number of buffed bytes</li>
</ul>

<br/>

### uint16_t dump()

Dumps all buffed bytes.

<b>Parameters</b>
<ul>
  <li>None</li>
</ul>

<b>Return</b>
<ul>
  <li><Number of dumped bytes/li>
</ul>

<br/>

### bool isFail()

Returns is buffer allocated unsuccessfully.

<b>Parameters</b>
<ul>
  <li>None</li>
</ul>

<b>Return</b>
<ul>
  <li>bool value</li>
</ul>

<br/>

### uint32_t lastBuff()

Returns `millis` when last buff occured.

<b>Parameters</b>
<ul>
  <li>None</li>
</ul>

<b>Return</b>
<ul>
  <li>uint32_t value</li>
</ul>

<br/><br/>

## KNOWN ISSUES

There is no known issues. If you find issue, open new issue at GitHub.



