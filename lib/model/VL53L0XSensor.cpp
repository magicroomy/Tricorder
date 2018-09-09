#include "Sensor.h"
#include "VL53L0XSensor.h"

VL53L0XSensor::VL53L0XSensor()
{
  distSensor = new VL53L0X()  ;
  distanceData = new SensorData();

}

void VL53L0XSensor::begin()
{
  isOK =true;

  distSensor->init();
  distSensor->setTimeout(500);
  distSensor->startContinuous(100);

}

void VL53L0XSensor::update()
{
  if ( isOK)
  {

    distanceData->setValue(((double)distSensor->readRangeContinuousMillimeters()) / 10) ;

  }
}

SensorData* VL53L0XSensor::getDistanceSensorData()
{
  return distanceData ;
}
