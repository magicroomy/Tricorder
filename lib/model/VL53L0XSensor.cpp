#include "Sensor.h"
#include "VL53L0XSensor.h"

VL53L0XSensor::VL53L0XSensor()
{
  distSensor = new VL53L0X()  ;
  distanceData = new SensorData();

}

bool VL53L0XSensor::begin()
{
  isOK =true;

  distSensor->init();
  distSensor->setTimeout(500);
  distSensor->startContinuous(100);

  return isOK ;

}

void VL53L0XSensor::update()
{
  if ( isOK)
  {

    double distance = ((double)distSensor->readRangeContinuousMillimeters()) / 10 ;
    if ( distance > 120)
      distance = 120 ;

    distanceData->setValue(distance) ;

  }
}

SensorData* VL53L0XSensor::getDistanceSensorData()
{
  return distanceData ;
}
