#include "Sensor.h"
#include "VEML6075Sensor.h"

VEML6075Sensor::VEML6075Sensor()
{
  uv = new VEML6075()  ;
  uvAData = new SensorData();
  uvBData = new SensorData();
  indexData = new SensorData();

}

bool VEML6075Sensor::begin()
{
  isOK = uv->begin() ;

  if (!isOK) {
    Serial.println("Unable to communicate with VEML6075.");

  }
  return isOK ; 
}

void VEML6075Sensor::update()
{
  if ( isOK)
  {

    uvAData->setValue(uv->uva()) ;
    uvBData->setValue(uv->uvb()) ;
    indexData->setValue(uv->index()) ;
  }
}

SensorData* VEML6075Sensor::getUVASensorData()
{
  return uvAData ;
}
SensorData* VEML6075Sensor::getUVBSensorData()
{
  return uvBData;
}
SensorData* VEML6075Sensor::getIndexSensorData()
{
  return indexData ;
}
