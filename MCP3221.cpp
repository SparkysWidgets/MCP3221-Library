/////////////////////////////////////////////////////////////////////////////
/*!

  MCP3221.cpp
  I2C Driver for Microchip's MCP3221 by Ryan Edwards, Sparkys Widgets
  
  Use this library with Sparkys Widgets MinipH, MinieC, IsoIon, IsoEC, and the ADCBreakout or any thing MCP3221 related

  I invest a lot of time and resources providing open source hardware, software, and tutorials 
  Please help support my efforts by purchasing products from www.sparkyswidgets.com, donating some time 
  on documentation or you can even donate some BitCoin to 1NwPNsf6t5vpph6AYY5bg361PSppPSSgDn

*/
/////////////////////////////////////////////////////////////////////////////

#include "MCP3221.h"

MCP3221::MCP3221(uint8_t adcAddress, int adcVRef) {
  I2CADCAddress = adcAddress;
  _adcVRef = adcVRef;
  _cnt = 0;
  _rollingTotal = 0;
  // We are going to assume that Wire.begin() has been called in setup()
}

/////////////////////////////////////////////////////////////////////////////
/*!


*/
/////////////////////////////////////////////////////////////////////////////

int MCP3221::readI2CADC(void) {

  uint16_t result;
  uint8_t numBytes = 2;
  Wire.requestFrom(I2CADCAddress, numBytes); // Tell our ADC to send out its data MSB, than LSB 
  if (Wire.available()) 
  {
    //taking the bitshift approach with a single variable
    //we are reading our MSB first so we can simply shift it 8 bits over, then read again
    result = Wire.read();
    result = result<<8;
    result += Wire.read();
  }

  return result;
}

/////////////////////////////////////////////////////////////////////////////
/*!


*/
/////////////////////////////////////////////////////////////////////////////

int MCP3221::calcMillivolts() {

  int mV = readI2CADC();
  mV = (((float)mV/4095)*_adcVRef); //MCP3221 is 12bit datasheet reports a full range of 4095 
  return (int)mV;
}

//Overloaded to accepted a raw iput
int MCP3221::calcMillivolts(int rawADC) {

	int mV = rawADC;
	mV = (((float)mV / 4095)*_adcVRef); //MCP3221 is 12bit datasheet reports a full range of 4095 
	return (int)mV;
}

/////////////////////////////////////////////////////////////////////////////
/*!


*/
/////////////////////////////////////////////////////////////////////////////

int MCP3221::calcRollingAVG() {

  uint16_t average, sum = 0;
  uint8_t i;

  //Part one drop the last reading and refactor array
  for (i = 1; i<NUMSAMPLES; i++)
  {
	  _samples[i - 1] = _samples[i];
  }
  //Add in the nweest sample in last place essentially the entire array is shifted now!
  //Maybe a better way to do this?
  _samples[NUMSAMPLES - 1] = readI2CADC();

  //Calculate our sum from the array with new data in and oldest data point dropped
  for (i = 0; i<NUMSAMPLES; i++)
  {
	  sum += _samples[i];
  }
  //and now finally our average
  average = sum / NUMSAMPLES;

  return average;
}

/////////////////////////////////////////////////////////////////////////////
/*!


*/
/////////////////////////////////////////////////////////////////////////////

int MCP3221::calcEMAVG() {

	static uint16_t exponential_average = readI2CADC();

	exponential_average = (ALPHA*(uint32_t)readI2CADC() + (POWER - ALPHA)*(uint32_t)exponential_average) / POWER;
	return exponential_average;
}


