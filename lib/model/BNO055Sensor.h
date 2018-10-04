#ifndef __BNO055SENSOR__
#define __BNO055SENSOR__

#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "Sensor.h"


class BNO055Sensor : public Sensor {

    public:
      BNO055Sensor() ;
      virtual void begin();
      virtual void update();
      SensorData* getRotationSensorData() ;
      SensorData* getRollSensorData() ;
      SensorData* getPitchSensorData() ;
      SensorData* getAccelXSensorData() ;
      SensorData* getAccelYSensorData() ;
      SensorData* getAccelZSensorData() ;


    private:
      Adafruit_BNO055 *bno ;
      
      SensorData *rotationData ;
      SensorData *rollData ;
      SensorData *pitchData ;
      SensorData *accelXData ;
      SensorData *accelYData ;
      SensorData *accelZData ;

      bool isOK = false ;
};

#endif
