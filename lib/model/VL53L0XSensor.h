#ifndef __VL53L0XSENSOR__
#define __VL53L0XSENSOR__

#include <VL53L0X.h>
#include "Sensor.h"

class VL53L0XSensor : public Sensor {

    public:
      VL53L0XSensor() ;
      virtual void begin();
      virtual void update();
      SensorData* getDistanceSensorData() ;
    private:
      VL53L0X *distSensor;
      SensorData *distanceData ;
      bool isOK = false ;
};

#endif
