#ifndef __CCS811SENSOR__
#define __CCS811SENSOR__

#include "Adafruit_CCS811.h"
#include "Sensor.h"

class CCS811Sensor : public Sensor {

    public:
      CCS811Sensor() ;
      virtual void begin();
      virtual void update();
      SensorData* getCO2SensorData() ;
      SensorData* getVOCSensorData() ;
    private:
      Adafruit_CCS811 *ccs;
      SensorData *co2Data ;
      SensorData *vocData ;
      bool isOK = false ;
};

#endif
