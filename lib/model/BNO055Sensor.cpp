#include "BNO055Sensor.h"

BNO055Sensor::BNO055Sensor()
{
   bno = Adafruit_BNO055(55);
  co2Data = new SensorData();
  vocData = new SensorData();

}

void BNO055Sensor::begin()
{
  isOK = bno.begin() ;

  if ( !isOK )
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
  }

}

void BNO055Sensor::update()
{
  if ( isOK )
  {
    
    sensors_event_t event;
    bno.getEvent(&event);


  }
}

SensorData* BNO055Sensor::getCO2SensorData()
{
  return co2Data ;
}

SensorData* BNO055Sensor::getVOCSensorData()
{
  return vocData ;
}
