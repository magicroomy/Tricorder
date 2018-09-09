#ifndef __VEML6075SENSOR__
#define __VEML6075SENSOR__

#include <SparkFun_VEML6075_Arduino_Library.h>
#include "Sensor.h"

class VEML6075Sensor : public Sensor {

    public:
      VEML6075Sensor() ;
      virtual void begin();
      virtual void update();
      SensorData* getUVASensorData() ;
      SensorData* getUVBSensorData() ;
      SensorData* getIndexSensorData() ;
    private:
      VEML6075 *uv; // Create a VEML6075 object
      SensorData *uvAData ;
      SensorData *uvBData ;
      SensorData *indexData ;
      bool isOK = false ;
};

#endif
