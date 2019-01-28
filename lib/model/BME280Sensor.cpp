#include "Sensor.h"
#include "BME280Sensor.h"

BME280Sensor::BME280Sensor()
{
  bme = new Adafruit_BME280()  ;
  tempData = new SensorData();
  humData = new SensorData();
  pressData = new SensorData();
}

bool BME280Sensor::begin()
{
  isOK = bme->begin(BME280_ADD);
  if (!isOK) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
  }
  return isOK ;
}

void BME280Sensor::update()
{
  if ( isOK)
  {

    tempData->setValue(bme->readTemperature()) ;
    humData->setValue(bme->readHumidity()) ;
    pressData->setValue(bme->readPressure()/100) ;
  }
}



SensorData* BME280Sensor::getTempSensorData()
{
  return tempData ;
}
SensorData* BME280Sensor::getHumSensorData()
{
  return humData;
}
SensorData* BME280Sensor::getPressSensorData()
{
  return pressData ;
}
