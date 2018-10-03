#ifndef __BNO055SENSOR__
#define __BNO055SENSOR__

#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "Sensor.h"

#define BNO055_SAMPLERATE_DELAY_MS (100)

class BNO055Sensor : public Sensor {

    public:
      BNO055Sensor() ;
      virtual void begin();
      virtual void update();
      SensorData* getCO2SensorData() ;
      SensorData* getVOCSensorData() ;
    private:
      Adafruit_BNO055 bno ;
      SensorData *co2Data ;
      SensorData *vocData ;
      bool isOK = false ;
};

#endif
