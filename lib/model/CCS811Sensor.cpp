#include "Sensor.h"
#include "CCS811Sensor.h"
#include "Adafruit_CCS811.h"

CCS811Sensor::CCS811Sensor()
{
  ccs = new Adafruit_CCS811()  ;
  co2Data = new SensorData();
  vocData = new SensorData();

}

void CCS811Sensor::begin()
{
  isOK =ccs->begin(  0x5B  ) ;
  // VOC
  if(!isOK){
    Serial.println("Failed to start CCS811 sensor! Please check your wiring.");
  }
  else
  {

      //calibrate temperature sensor
      while(!ccs->available());
      float temp = ccs->calculateTemperature();
      ccs->setTempOffset(temp - 25.0);
      ccs->setDriveMode(CCS811_DRIVE_MODE_1SEC) ;

  }


}

void CCS811Sensor::update()
{
  if ( isOK)
  {
    if(ccs->available()){
      uint8_t stat = ccs->readData() ;
      ccs->calculateTemperature();
      co2Data->setValue( ccs->geteCO2() );
      vocData->setValue( ccs->getTVOC() );
    }
  }
}

SensorData* CCS811Sensor::getCO2SensorData()
{
  return co2Data ;
}

SensorData* CCS811Sensor::getVOCSensorData()
{
  return vocData ;
}
