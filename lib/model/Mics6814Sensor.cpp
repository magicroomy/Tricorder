#include "Mics6814Sensor.h"

Mics6814Sensor::Mics6814Sensor()
{
  nh3Data = new SensorData();
  coData = new SensorData();
  no2Data = new SensorData();
  c3h8Data = new SensorData();
  c4h10Data = new SensorData();
  ch4Data = new SensorData();
  h2Data = new SensorData();
  c2h5ohData = new SensorData();
}

bool Mics6814Sensor::begin()
{
  isOK = true ;
  gas.begin(0x04); //the default I2C address of the slave is 0x04
  gas.powerOn();
  return isOK ;

}

void Mics6814Sensor::update()
{
  if ( isOK)
  {


    nh3Data->setValue( gas.measure_NH3());
    coData->setValue( gas.measure_CO());
    no2Data->setValue( gas.measure_NO2());
    c3h8Data->setValue( gas.measure_C3H8());
    c4h10Data->setValue( gas.measure_C4H10());
    ch4Data->setValue( gas.measure_CH4());
    h2Data->setValue( gas.measure_H2());
    c2h5ohData->setValue( gas.measure_C2H5OH());
  }
}

SensorData* Mics6814Sensor::getNH3SensorData()
{
  return nh3Data ;
}
SensorData* Mics6814Sensor::getCOSensorData()
{
  return coData ;
}
SensorData* Mics6814Sensor::getNO2SensorData()
{
  return no2Data ;
}
SensorData* Mics6814Sensor::getC3H8SensorData()
{
  return c3h8Data ;
}
SensorData* Mics6814Sensor::getC4H10SensorData()
{
  return c4h10Data ;
}
SensorData* Mics6814Sensor::getCH4SensorData()
{
  return ch4Data ;
}
SensorData* Mics6814Sensor::getH2SensorData()
{
  return h2Data ;
}
SensorData* Mics6814Sensor::getC2H5OHSensorData()
{
  return c2h5ohData ;
}

