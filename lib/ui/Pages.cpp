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
  Serial.println("INIT BLANK PAGE");
  GO.lcd.drawJpgFile(SPIFFS, "/Init.jpg", 0, 0, 320, 240, 0, 0, JPEG_DIV_NONE);
}

void BlankPage::draw()
{
}
// -------------------------------------------

void AmbientPage::init()
{
  Serial.println("INIT Ambient PAGE");
  GO.lcd.drawJpgFile(SPIFFS, "/Ambient.jpg", 0, 0, 320, 240, 0, 0, JPEG_DIV_NONE);
  for (int i = 0; i < 5; ++i)
  {
    components[i]->reset();
  }
}

void AmbientPage::setSensorData(
    SensorData *tempSensorData,
    SensorData *humSensorData,
    SensorData *pressSensorData,
    SensorData *luxSensorData,
    SensorData *uvSensorData)
{
  this->tempSensorData = tempSensorData;
  this->humSensorData = humSensorData;
  this->pressSensorData = pressSensorData;
  this->luxSensorData = luxSensorData;
  this->uvSensorData = uvSensorData;

  components = (UIComponent **)malloc(sizeof(UIComponent *) * 5);

  components[0] = new Text(68, 33, "%.1lf", RED, BLACK, 2, tempSensorData);
  components[1] = new Text(68, 73, "%.1lf", BLUE, BLACK, 2, humSensorData);
  components[2] = new Text(68, 112, "%.1lf", WHITE, BLACK, 2, pressSensorData);
  components[3] = new Text(68, 152, "%.1lf", WHITE, BLACK, 2, luxSensorData);
  components[4] = new Text(68, 192, "%.1lf", WHITE, BLACK, 2, uvSensorData);
}

void AmbientPage::draw()
{
  for (int i = 0; i < 5; ++i)
  {
    components[i]->draw();
  }
}
// -------------------------------------------

void LightPage::init()
{
  Serial.println("INIT Light PAGE");
  GO.lcd.drawJpgFile(SPIFFS, "/Light.jpg", 0, 0, 320, 240, 0, 0, JPEG_DIV_NONE);
  for (int i = 0; i < 5; ++i)
  {
    components[i]->reset();
  }
}

void LightPage::setSensorData(
    SensorData *redSensorData,
    SensorData *greenSensorData,
    SensorData *blueSensorData,
    SensorData *luxSensorData,
    SensorData *colorTempSensorData)
{
  this->redSensorData = redSensorData;
  this->greenSensorData = greenSensorData;
  this->blueSensorData = blueSensorData;
  this->luxSensorData = luxSensorData;
  this->colorTempSensorData = colorTempSensorData;

  components = (UIComponent **)malloc(sizeof(UIComponent *) * 5);

  components[0] = new BarGraph(68, 33, 220, 35, 0, 100, RED, BLACK, redSensorData);
  components[1] = new BarGraph(68, 74, 220, 35, 0, 100, GREEN, BLACK, greenSensorData);
  components[2] = new BarGraph(68, 112, 220, 35, 0, 100, BLUE, BLACK, blueSensorData);

  //components[0] = new Text(65, 30, "%.1lf", RED, BLACK, 2, redSensorData);
  //components[1] = new Text(65, 72, "%.1lf", GREEN, BLACK, 2, greenSensorData);
  //components[2] = new Text(65, 112, "%.1lf", BLUE, BLACK, 2, blueSensorData);
  components[3] = new Text(68, 153, "%.1lf", WHITE, BLACK, 2, luxSensorData);
  components[4] = new Text(68, 192, "%.1lf", YELLOW, BLACK, 2, colorTempSensorData);
}

void LightPage::draw()
{
  for (int i = 0; i < 5; ++i)
  {
    components[i]->draw();
  }
}

// -------------------------------------------

void GasesPage::init()
{
  Serial.println("INIT Gases PAGE");
  GO.lcd.drawJpgFile(SPIFFS, "/Gases.jpg", 0, 0, 320, 240, 0, 0, JPEG_DIV_NONE);
  for (int i = 0; i < 8; ++i)
  {
    components[i]->reset();
  }
}

void GasesPage::setSensorData(
    SensorData *nh3Data,
    SensorData *coData,
    SensorData *no2Data,
    SensorData *c3h8Data,
    SensorData *c4h10Data,
    SensorData *ch4Data,
    SensorData *h2Data,
    SensorData *c2h5ohData,
    SensorData *co2Data,
    SensorData *vocData)
{
  this->nh3Data = nh3Data;
  this->coData = coData;
  this->no2Data = no2Data;
  this->c3h8Data = c3h8Data;
  this->c4h10Data = c4h10Data;
  this->ch4Data = ch4Data;
  this->h2Data = h2Data;
  this->c2h5ohData = c2h5ohData;
  this->co2Data = co2Data;
  this->vocData = vocData;

  components = (UIComponent **)malloc(sizeof(UIComponent *) * 10);

  components[0] = new Text(65, 30, "%.1lf", RED, BLACK, 2, coData);
  components[1] = new Text(65, 72, "%.1lf", GREEN, BLACK, 2, no2Data);
  components[2] = new Text(65, 112, "%.1lf", BLUE, BLACK, 2, nh3Data);
  components[3] = new Text(65, 150, "%.1lf", WHITE, BLACK, 2, c3h8Data);
  components[4] = new Text(65, 190, "%.1lf", YELLOW, BLACK, 2, co2Data);

  components[5] = new Text(225, 30, "%.1lf", RED, BLACK, 2, h2Data);
  components[6] = new Text(225, 72, "%.1lf", GREEN, BLACK, 2, c2h5ohData);
  components[7] = new Text(225, 112, "%.1lf", BLUE, BLACK, 2, ch4Data);
  components[8] = new Text(225, 150, "%.1lf", WHITE, BLACK, 2, c4h10Data);
  components[9] = new Text(225, 190, "%.1lf", YELLOW, BLACK, 2, vocData);
}

void GasesPage::draw()
{
  for (int i = 0; i < 10; ++i)
  {
    components[i]->draw();
  }
}

// -------------------------------------------

void DistancePage::init()
{
  Serial.println("INIT Distance PAGE");
  GO.lcd.drawJpgFile(SPIFFS, "/Distance.jpg", 0, 0, 320, 240, 0, 0, JPEG_DIV_NONE);
  for (int i = 0; i < 2; ++i)
  {
    components[i]->reset();
  }
}

void DistancePage::setSensorData(SensorData *distanceData)
{
  this->distanceData = distanceData;

  components = (UIComponent **)malloc(sizeof(UIComponent *) * 2);

  // BarGraph(int x, int y, int width, int height, double min, double max, SensorData *data) ;

  components[0] = new BarGraph(68, 35, 220, 35, 0, 120, WHITE, BLACK, distanceData);
  components[1] = new Text(68, 90, "%.1lf", YELLOW, BLACK, 4, distanceData);
}

void DistancePage::draw()
{
  for (int i = 0; i < 2; ++i)
  {
    components[i]->draw();
  }
}

// -------------------------------------------

void TemperaturePage::init()
{
  Serial.println("INIT Temperature PAGE");
  GO.lcd.drawJpgFile(SPIFFS, "/Temperature.jpg", 0, 0, 320, 240, 0, 0, JPEG_DIV_NONE);
  for (int i = 0; i < 2; ++i)
  {
    components[i]->reset();
  }
}

void TemperaturePage::setSensorData(SensorData *temperatureData)
{
  this->temperatureData = temperatureData;

  components = (UIComponent **)malloc(sizeof(UIComponent *) * 2);

  // BarGraph(int x, int y, int width, int height, double min, double max, SensorData *data) ;

  components[0] = new BarGraph(68, 35, 220, 35, 0, 120, RED, BLACK, temperatureData);
  components[1] = new Text(68, 90, "%.1lf", YELLOW, BLACK, 4, temperatureData);
}

void TemperaturePage::draw()
{
  for (int i = 0; i < 2; ++i)
  {
    components[i]->draw();
  }
}

// -------------------------------------------

void OrientationPage::init()
{
  Serial.println("INIT Orientation PAGE");
  GO.lcd.drawJpgFile(SPIFFS, "/Orientation.jpg", 0, 0, 320, 240, 0, 0, JPEG_DIV_NONE);
}

void OrientationPage::setSensorData(SensorData *yawData, SensorData *rollData, SensorData *pitchData)
{
  this->yawData = yawData;
  this->rollData = rollData;
  this->pitchData = pitchData;

  rollText = new Text(60, 190, "%.1lf", BLUE, BLACK, 2, rollData);
  pitchText = new Text(60, 190, "%.1lf", BLUE, BLACK, 2, pitchData);
  yawText = new Text(145, 185, "%.1lf", YELLOW, BLACK, 2, yawData);
}

void OrientationPage::draw()
{
  double pitch = pitchData->getValue();
  double roll = rollData->getValue();
  
  if (pitch > 0)
  {
    pitchText->setPosition(250, 42);
  }
  else
  {
    pitchText->setPosition(250, 150);
  }

  if (roll > 0)
  {
    rollText->setPosition(10, 42);
  }
  else
  {
    rollText->setPosition(10, 150);
  }

  if ( lastRoll < 0 && roll > 0)
  {
    GO.lcd.fillRect(10,150, 57, 16, BLACK) ;
  }

  if ( lastRoll > 0 && roll < 0)
  {
    GO.lcd.fillRect(10,42, 57, 16, BLACK) ;
  }


  if ( lastPitch < 0 && pitch > 0)
  {
    GO.lcd.fillRect(250,150, 57, 16, BLACK) ;
  }

  if ( lastPitch > 0 && pitch < 0)
  {
    GO.lcd.fillRect(250,42, 57, 16, BLACK) ;
  }

  lastPitch = pitch ;
  lastRoll = roll ;

  pitchText->draw();
  rollText->draw();
  yawText->draw();
}

// -------------------------------------------

void ExamplePage::init()
{
  Serial.println("INIT Gases PAGE");
  GO.lcd.fillRect(0, 0, 320, 240, BLACK);
  for (int i = 0; i < 5; ++i)
  {
    components[i]->reset();
  }
}

void ExamplePage::setSensorData(
    SensorData *irTemp,
    SensorData *distData,
    SensorData *rotationData,
    SensorData *pitchData,
    SensorData *rollData,
    SensorData *accXData,
    SensorData *accYData,
    SensorData *accZData)
{
  this->irTemp = irTemp;
  this->distData = distData;
  this->rotationData = rotationData;
  this->pitchData = pitchData;
  this->rollData = rollData;
  this->accXData = accXData;
  this->accYData = accYData;
  this->accZData = accZData;

  components = (UIComponent **)malloc(sizeof(UIComponent *) * 8);

  components[0] = new Text(65, 30, "%.1lf", RED, BLACK, 2, irTemp);
  components[1] = new Text(65, 72, "%.1lf", GREEN, BLACK, 2, distData);
  components[2] = new Text(65, 112, "%.1lf", BLUE, BLACK, 2, rotationData);
  components[3] = new Text(65, 150, "%.1lf", WHITE, BLACK, 2, pitchData);
  components[4] = new Text(65, 190, "%.1lf", YELLOW, BLACK, 2, rollData);
  components[5] = new Text(225, 112, "%.1lf", BLUE, BLACK, 2, accXData);
  components[6] = new Text(225, 150, "%.1lf", WHITE, BLACK, 2, accYData);
  components[7] = new Text(225, 190, "%.1lf", YELLOW, BLACK, 2, accZData);
}

void ExamplePage::draw()
{
  for (int i = 0; i < 8; ++i)
  {
    components[i]->draw();
  }
}
