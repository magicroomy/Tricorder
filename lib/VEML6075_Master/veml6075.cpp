/*

The MIT License (MIT)

Copyright (c) 2016 Lei.wang

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
#include "Arduino.h"
#include "Wire.h"
#include "VEML6075.h"

#define NUM_INTEGRATION_TIMES 5

const float HD_SCALAR = 2.0;

const float UV_ALPHA = 1.0;
const float UV_BETA = 1.0;
const float UV_GAMMA = 1.0;
const float UV_DELTA = 1.0;

const float UVA_A_COEF = 2.22;
const float UVA_B_COEF = 1.33;
const float UVA_C_COEF = 2.95;
const float UVA_D_COEF = 1.75;

const float UVA_RESPONSIVITY_100MS_UNCOVERED = 0.001111;
const float UVB_RESPONSIVITY_100MS_UNCOVERED = 0.00125;

const float UVA_RESPONSIVITY[NUM_INTEGRATION_TIMES] =
{
    UVA_RESPONSIVITY_100MS_UNCOVERED / 0.5016286645, // 50ms
    UVA_RESPONSIVITY_100MS_UNCOVERED,                // 100ms
    UVA_RESPONSIVITY_100MS_UNCOVERED / 2.039087948,  // 200ms
    UVA_RESPONSIVITY_100MS_UNCOVERED / 3.781758958,  // 400ms
    UVA_RESPONSIVITY_100MS_UNCOVERED / 7.371335505   // 800ms
};

const float UVB_RESPONSIVITY[NUM_INTEGRATION_TIMES] =
{
    UVB_RESPONSIVITY_100MS_UNCOVERED / 0.5016286645, // 50ms
    UVB_RESPONSIVITY_100MS_UNCOVERED,                // 100ms
    UVB_RESPONSIVITY_100MS_UNCOVERED / 2.039087948,  // 200ms
    UVB_RESPONSIVITY_100MS_UNCOVERED / 3.781758958,  // 400ms
    UVB_RESPONSIVITY_100MS_UNCOVERED / 7.371335505   // 800ms
};


VEML6075::VEML6075(void) {
  _aResponsivity = UVA_RESPONSIVITY[3];   // 400ms
     _bResponsivity = UVB_RESPONSIVITY[3];
}

bool VEML6075::begin(void) {
  bool sensorExists;
  Wire.beginTransmission(VEML6075_I2C_ADDRESS);
  if (Wire.endTransmission() == 0) {
    sensorExists = true;
  }
  return sensorExists;
}

void VEML6075::setConfiguration(uint8_t configuration) {
  Wire.beginTransmission(VEML6075_I2C_ADDRESS);
  Wire.write(COMMAND_CODE_CONF);
  Wire.write(configuration);
  Wire.write(0);
  Wire.endTransmission();
  lastConfiguration = configuration;
}

uint16_t VEML6075::read(uint8_t commandCode) {
  uint16_t data = 0;

  Wire.beginTransmission(VEML6075_I2C_ADDRESS);
  Wire.write(commandCode);
  Wire.endTransmission(false); // false
  Wire.requestFrom(VEML6075_I2C_ADDRESS,2);

int readable = 0 ;

  do {
     readable = Wire.available() ;
  } while(readable != 2) ;

  data = Wire.read();
  data |= Wire.read() << 8;


  return data;
}

float VEML6075::getUVA(void) {
  float uva = (float)getRawUVA() - ((UVA_A_COEF * UV_ALPHA * getUVC1()) / UV_GAMMA)
                             - ((UVA_B_COEF * UV_ALPHA * getUVC2()) / UV_DELTA);


  return uva ;
}

float VEML6075::getUVB(void) {
  float uvb = (float)getRawUVB() - ((UVA_C_COEF * UV_BETA * getUVC1()) / UV_GAMMA)
                             - ((UVA_D_COEF * UV_BETA * getUVC2()) / UV_DELTA);

  return uvb ;
}


uint16_t VEML6075::getRawUVA(void) {
  return(read(COMMAND_CODE_UVA));
}

uint16_t VEML6075::getRawUVB(void) {
  return(read(COMMAND_CODE_UVB));
}


uint16_t VEML6075::getUVC1(void) {
  return(read(COMMAND_CODE_UVC1));
}

uint16_t VEML6075::getUVC2(void) {
  return(read(COMMAND_CODE_UVC2));
}

uint16_t VEML6075::getUVD(void) {
  return(read(COMMAND_CODE_UVD));
}

uint16_t VEML6075::ReadDeviceID(void){
	return(read(COMMAND_CODE_DeviceID));
}

float VEML6075::getIndex(void)
{
    uint16_t uva;
    uint16_t uvb;
    uint16_t uvComp1;
    uint16_t uvComp2;

    /*if ((_lastReadTime + _integrationTime) > millis())
    {
        return _lastIndex;
    }*/

    float uvaCalc = this->getUVA();
    float uvbCalc = this->getUVB();

    float uvia = uvaCalc * (1.0 / UV_ALPHA) * _aResponsivity;
    float uvib = uvbCalc * (1.0 / UV_BETA) * _bResponsivity;
    float index  = (uvia + uvib) / 2.0;

    // NO HD


    return index;
}
