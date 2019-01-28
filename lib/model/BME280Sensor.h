#ifndef __BME280SENSOR__
#define __BME280SENSOR__

#include "Adafruit_BME280.h"
#include "Sensor.h"

#define BME280_ADD 0x77

class BME280Sensor : public Sensor {

    public:
      BME280Sensor() ;
      virtual bool begin();
      virtual void update();
      SensorData* getTempSensorData() ;
      SensorData* getHumSensorData() ;
      SensorData* getPressSensorData() ;
    private:
      Adafruit_BME280 *bme;
      SensorData *tempData ;
      SensorData *humData ;
      SensorData *pressData ;
      bool isOK = false ;
};

#endif
