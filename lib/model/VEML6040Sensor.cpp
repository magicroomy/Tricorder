#include "VEML6040Sensor.h"

VEML6040Sensor::VEML6040Sensor()
{
  redData = new SensorData();
  greenData= new SensorData();
  blueData= new SensorData();
  luxData= new SensorData();
  colorTempData= new SensorData();

}

// Retrieve data from the sensor and do the calculations
void VEML6040Sensor::update(void) {

  if ( isOK) 
  {

  uint16_t redF = RGBWSensor->getRed();
  uint16_t greenF = RGBWSensor->getGreen();
  uint16_t blueF = RGBWSensor->getBlue();


  double sum = ((double)redF) + ((double)greenF) +((double) blueF);
  double r = (redF / sum * 100);
  double g = (greenF / sum * 100);
  double b = (blueF / sum * 100);

  redData->setValue(r) ;
  greenData->setValue(g) ;
  blueData->setValue(b) ;
  luxData->setValue( (double) RGBWSensor->getAmbientLight()) ;
  colorTempData->setValue((double) RGBWSensor->getCCT()) ;
  }
  
}

void VEML6040Sensor::begin()
{
  RGBWSensor = new VEML6040() ;
  isOK = RGBWSensor->begin() ;
  if ( !isOK )  
  {
    Serial.println("Unable to detect VEML 6040") ;
  }
  else
  {
    RGBWSensor->setConfiguration(VEML6040_IT_160MS + VEML6040_AF_AUTO + VEML6040_SD_ENABLE);
  }

}

SensorData *VEML6040Sensor::getRedSensorData()
{
  return redData;
}

SensorData *VEML6040Sensor::getGreenSensorData()
{
  return greenData;
}

SensorData *VEML6040Sensor::getBlueSensorData()
{
  return blueData;
}

SensorData *VEML6040Sensor::getLuxSensorData()
{
  return luxData;
}

SensorData *VEML6040Sensor::getColorTempSensorData()
{
  return colorTempData;
}
