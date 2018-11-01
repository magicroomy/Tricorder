#include "BNO055Sensor.h"

BNO055Sensor::BNO055Sensor()
{
  bno = new Adafruit_BNO055(55);
  rotationData = new SensorData();
  rollData = new SensorData();
  pitchData = new SensorData();
  accelXData = new SensorData();
  accelYData = new SensorData();
  accelZData = new SensorData();

}

void BNO055Sensor::begin()
{
  
  isOK = bno->begin(Adafruit_BNO055::adafruit_bno055_opmode_t::OPERATION_MODE_NDOF) ;

  

  if ( !isOK )
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
  }
  else{
    delay(1000); // FUNDAMENTAL !!!
    /* Use external crystal for better accuracy */
    bno->setExtCrystalUse(true);

  }
}

void BNO055Sensor::update()
{
  if ( isOK )
  {
    
    imu::Vector<3> orientation = bno->getVector(Adafruit_BNO055::adafruit_vector_type_t::VECTOR_EULER) ;
    imu::Vector<3> accel = bno->getVector(Adafruit_BNO055::adafruit_vector_type_t::VECTOR_ACCELEROMETER) ;

    rotationData->setValue(orientation.x()) ;
    rollData->setValue(orientation.y()) ;
    pitchData->setValue(orientation.z()) ;

    accelXData->setValue(accel.x()/10) ;
    accelYData->setValue(accel.y()/10) ;
    accelZData->setValue(accel.z()/10) ;


  }
}

SensorData* BNO055Sensor::getRotationSensorData()
{
  return rotationData ;
}

SensorData* BNO055Sensor::getRollSensorData()
{
  return rollData ;
}

SensorData* BNO055Sensor::getPitchSensorData()
{
  return pitchData ;
}

SensorData* BNO055Sensor::getAccelXSensorData()
{
  return accelXData ;
}

SensorData* BNO055Sensor::getAccelYSensorData()
{
  return accelYData ;
}

SensorData* BNO055Sensor::getAccelZSensorData()
{
  return accelZData ;
}






