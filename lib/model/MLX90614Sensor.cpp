#include "Sensor.h"
#include "MLX90614Sensor.h"

MLX90614Sensor::MLX90614Sensor()
{
  tempSensor = new IRTherm()  ;
  tempData = new SensorData();

}

bool MLX90614Sensor::begin()
{
  isOK =true;
  tempSensor->begin(0x5a); // Initialize thermal IR sensor
  tempSensor->setUnit(TEMP_C); // Set the library's units to Farenheit
  return isOK ;
}

void MLX90614Sensor::update()
{
  if ( isOK)
  {
    if (tempSensor->read()) // On success, read() will return 1, on fail 0.
    {
      tempData->setValue( (double) tempSensor->object() );

    }
  }
}

SensorData* MLX90614Sensor::getTempSensorData()
{
  return tempData ;
}
