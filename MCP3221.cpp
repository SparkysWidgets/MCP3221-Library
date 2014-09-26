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
    //we are reading our MSB first so we can simple shift it 8 bits over, then read again
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
  mV = (((float)mV/4095)*_adcVRef);
  return (int)mV;
}

/////////////////////////////////////////////////////////////////////////////
/*!


*/
/////////////////////////////////////////////////////////////////////////////

int MCP3221::calcRollingAVG() {

  int AVG, temp;
  temp = (((float)temp/4095)*_adcVRef);
  return AVG;
}


