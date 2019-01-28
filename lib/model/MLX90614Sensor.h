#ifndef __MLX90614SENSOR__
#define __MLX90614SENSOR__

#include <SparkFunMLX90614.h> // SparkFunMLX90614 Arduino library
#include "Sensor.h"

class MLX90614Sensor : public Sensor {

    public:
      MLX90614Sensor() ;
      virtual bool begin();
      virtual void update();
      SensorData* getTempSensorData() ;
    private:
      IRTherm *tempSensor;
      SensorData *tempData ;
      bool isOK = false ;
};

#endif
