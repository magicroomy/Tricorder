#ifndef __VEML6040SENSOR__
#define __VEML6040SENSOR__

#include "Sensor.h"
#include <veml6040.h>
#include "Arduino.h"

class VEML6040Sensor : public Sensor
{

public:
  VEML6040Sensor();
  virtual bool begin();
  virtual void update();
  SensorData *getRedSensorData();
  SensorData *getGreenSensorData();
  SensorData *getBlueSensorData();
  SensorData *getLuxSensorData();
  SensorData *getColorTempSensorData();

private:
  
  VEML6040 *RGBWSensor;

  SensorData *redData;
  SensorData *greenData;
  SensorData *blueData;
  SensorData *luxData;
  SensorData *colorTempData;
  bool isOK = false;
};
  #endif
