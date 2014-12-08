Welcome To: MCP3221 Driver Library
================================


##### Note: This can be used with any AVR/Arduino that needs to interface with hardware that is based on an MCP3221

Originally written as a simple interface this driver has been extended with a couple simple averaging methods, and makes taking readings very easy.

Class Info
-------------------------

- Simple implementation with instancing (MCP3221 mcp3221(address,vref) for example)
- Feed it address and and measured VREF(I.E measured VDD into IC)


Method Info
-------------------------

- readI2CADC, takes a single reading from the MCP3221 which is in constant conversion mode by default(IIRC its always in this mode)
- calcMillivolts, calls readI2CADC and uses VREF value that was input during instance creation
- calcRollingAVG, Takes current raw adc reading and adds it to a storage array(default is 10 data points), th oldest data point is dropped and array is shifted to move with readings
- calcEMAVG, approximates a rolling average by using an ALPHA coefficient and a power of 2 POWER for division, only needs a current reading which is weighted by ALPHA is pass through


Average and Smoothing Info
-------------------------

##### Quick list of Smoothing methods used in this driver
- Rolling/Moving average, uses an array to store data points, oldest is removed and current reading is added in as array is shifted to move with dataset
- Exponential moving average using power of 2 division(POWER) to avoid unnecessary float math, approximates a moving average while only using current data point


License Info
-------------------------

<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/88x31.png" /></a><br /><span xmlns:dct="http://purl.org/dc/terms/" property="dct:title">MCP3221 Library</span> by <a xmlns:cc="http://creativecommons.org/ns#" href="http://www.sparkyswidgets.com/" property="cc:attributionName" rel="cc:attributionURL">Ryan Edwards, Sparky's Widgets</a> is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.