#ifndef __MICS6814SENSOR__
#define __MICS6814SENSOR__

#include <MutichannelGasSensor.h>
#include "Sensor.h"

class Mics6814Sensor : public Sensor {

    public:
      Mics6814Sensor() ;
      virtual bool begin();
      virtual void update();
      SensorData* getNH3SensorData() ;
      SensorData* getCOSensorData() ;
      SensorData* getNO2SensorData() ;
      SensorData* getC3H8SensorData() ;
      SensorData* getC4H10SensorData() ;
      SensorData* getCH4SensorData() ;
      SensorData* getH2SensorData() ;
      SensorData* getC2H5OHSensorData() ;


    private:
      SensorData *nh3Data ;
      SensorData *coData ;
      SensorData *no2Data ;
      SensorData *c3h8Data ;
      SensorData *c4h10Data ;
      SensorData *ch4Data ;
      SensorData *h2Data ;
      SensorData *c2h5ohData ;

      bool isOK = false ;
};

#endif
