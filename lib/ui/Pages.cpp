#include "UIComponents.h"
#include "Pages.h"
#include <odroid_go.h>
#include "Arduino.h"


#include "FS.h"
#include "SPIFFS.h"

// --------------------------------------------------------------------

// --------------------------------------------------------------------

void BlankPage::init()
{
  Serial.println("INIT BLANK PAGE") ;
  GO.lcd.drawJpgFile(SPIFFS, "/Init.jpg", 0, 0, 320, 240, 0, 0, JPEG_DIV_NONE) ;
}

void BlankPage::draw()
{
}
// -------------------------------------------



void AmbientPage::init()
{
  Serial.println("INIT Ambient PAGE") ;
  GO.lcd.drawJpgFile(SPIFFS, "/Ambient.jpg", 0, 0, 320, 240, 0, 0, JPEG_DIV_NONE) ;
}

void AmbientPage::setSensorData(
  SensorData *tempSensorData,
  SensorData *humSensorData,
  SensorData *pressSensorData,
  SensorData *luxSensorData,
  SensorData *uvSensorData
)
{
  this->tempSensorData = tempSensorData;
  this->humSensorData = humSensorData;
  this->pressSensorData = pressSensorData;
  this->luxSensorData = luxSensorData;
  this->uvSensorData = uvSensorData;

  components  = (UIComponent **) malloc(sizeof(UIComponent *) * 5);

  components[0] = new Text(65,30, "%.1lf", RED, BLACK, 2 ,tempSensorData) ;
  components[1] = new Text(65,72, "%.1lf", BLUE, BLACK, 2 ,humSensorData) ;
  components[2] = new Text(65, 112, "%.1lf", WHITE, BLACK, 2 ,pressSensorData) ;
  components[3] = new Text(65,150, "%.1lf", WHITE, BLACK, 2 ,luxSensorData) ;
  components[4] = new Text(65,190, "%.1lf", WHITE, BLACK, 2 ,uvSensorData) ;

}

void AmbientPage::draw()
{
  for ( int i = 0 ; i < 5 ; ++i )
  {
    components[i]->draw() ;
  }
}
// -------------------------------------------


void LightPage::init()
{
  Serial.println("INIT Light PAGE") ;
   GO.lcd.drawJpgFile(SPIFFS, "/Light.jpg", 0, 0, 320, 240, 0, 0, JPEG_DIV_NONE) ;
}

void LightPage::setSensorData(
  SensorData *redSensorData,
  SensorData *greenSensorData,
  SensorData *blueSensorData,
  SensorData *luxSensorData,
  SensorData *colorTempSensorData
)
{
  this->redSensorData = redSensorData;
  this->greenSensorData = greenSensorData;
  this->blueSensorData = blueSensorData;
  this->luxSensorData = luxSensorData;
  this->colorTempSensorData = colorTempSensorData;

  components  = (UIComponent **) malloc(sizeof(UIComponent *) * 5);

  components[0] = new Text(65,30, "%.1lf", RED, BLACK, 2 ,redSensorData) ;
  components[1] = new Text(65,72, "%.1lf", GREEN, BLACK, 2 ,greenSensorData) ;
  components[2] = new Text(65, 112, "%.1lf", BLUE, BLACK, 2 ,blueSensorData) ;
  components[3] = new Text(65,150, "%.1lf", WHITE, BLACK, 2 ,luxSensorData) ;
  components[4] = new Text(65,190, "%.1lf", YELLOW, BLACK, 2 ,colorTempSensorData) ;

}

void LightPage::draw()
{
  for ( int i = 0 ; i < 5 ; ++i )
  {
    components[i]->draw() ;
  }
}
