#ifndef __I2CSWITCHSENSOR__
#define __I2CSWITCHSENSOR__


#include "Sensor.h"
#include <Wire.h>
#include <Arduino.h>


#define TCA9543A_ADDRESS 0x70

class I2CSWITCHSensor : public Sensor {

    public:
      I2CSWITCHSensor(int channel) ;
      virtual void begin();
      virtual void update();
    private:
      bool isOK = false ;
      int channel = 0 ;
      uint8_t selectChannel(uint8_t channel) ;
};

#endif
