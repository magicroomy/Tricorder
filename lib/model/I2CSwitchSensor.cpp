#include "I2CSwitchSensor.h"

I2CSWITCHSensor::I2CSWITCHSensor(int channel)
{
 this->channel = channel ;
}

void I2CSWITCHSensor::begin()
{
   Wire.beginTransmission(TCA9543A_ADDRESS);
  uint8_t error = Wire.endTransmission();

  if ( error == 0 )
  {
    isOK = true  ;
  }
  else
  {
    Serial.println("Unable to find Switch") ;
  }


}

void I2CSWITCHSensor::update()
{
  if ( isOK )
  {
    selectChannel(channel) ;
    Serial.printf("Switch to Channel %d\n", channel) ;
  }
}


uint8_t I2CSWITCHSensor::selectChannel(uint8_t channel) {

	if (channel >= 0 && channel < 4) {
		Wire.beginTransmission(TCA9543A_ADDRESS);
		switch (channel) {
		case 0:
			Wire.write(0x01);
			break;
		case 1:
			Wire.write(0x02);
			break;
		case 2:
			Wire.write(0x04);
			break;
		case 3:
			Wire.write(0x08);
			break;
		}
		return Wire.endTransmission();
	}
	else {
		return 0xff;
	}
}