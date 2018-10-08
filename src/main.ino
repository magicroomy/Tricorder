#include "WiFiServer.h"
#include "WiFiClientSecure.h"
#include <odroid_go.h>
#include <Wire.h>

#include "FS.h"
#include "SPIFFS.h"

#include "BME280Sensor.h"
#include "VEML6075Sensor.h"
#include "VEML6040Sensor.h"
#include "VL53L0XSensor.h"
#include "CCS811Sensor.h"
#include "MLX90614Sensor.h"
#include "TCS34725Sensor.h"
#include "I2CSwitchSensor.h"
#include "Mics6814Sensor.h"
#include "BNO055Sensor.h"
#include "Sensor.h"

#include "Pages.h"
#include "UIComponents.h"

#define SDA 15
#define SCK 4

BME280Sensor *bmeSensor = new BME280Sensor() ;
VEML6075Sensor *veml6075Sensor = new VEML6075Sensor() ;
VL53L0XSensor *vl53l0xSensor = new VL53L0XSensor() ;
CCS811Sensor *ccs811Sensor = new CCS811Sensor() ;
MLX90614Sensor *mlx90614Sensor = new MLX90614Sensor() ;
TCS34725Sensor *tcs34725Sensor = new TCS34725Sensor() ;
VEML6040Sensor *veml6040Sensor = new VEML6040Sensor() ;
Mics6814Sensor *mics6814Sensor = new Mics6814Sensor() ;
I2CSWITCHSensor *channel0Sensor = new I2CSWITCHSensor(0) ;
I2CSWITCHSensor *channel1Sensor = new I2CSWITCHSensor(1) ;
BNO055Sensor *bno055Sensor = new BNO055Sensor() ;

Sensor *sensorlist[] = { channel1Sensor, vl53l0xSensor, bmeSensor, veml6075Sensor, mlx90614Sensor, channel0Sensor, veml6040Sensor, ccs811Sensor, mics6814Sensor, bno055Sensor};

AmbientPage *ambientPage = new AmbientPage() ;
LightPage *lightPage = new LightPage() ;
BlankPage *blankPage = new BlankPage() ;
GasesPage *gasesPage = new GasesPage() ;
ExamplePage *examplePage = new ExamplePage() ;
DistancePage *distancePage = new DistancePage() ;
TemperaturePage *temperaturePage = new TemperaturePage() ;
OrientationPage *orientationPage = new OrientationPage() ;
Page *pageList[] = {ambientPage, lightPage, gasesPage, distancePage,temperaturePage, orientationPage} ;

int currentPage = -1 ;
int pages = 6 ;

void initPages()
{
  ambientPage->setSensorData( bmeSensor->getTempSensorData(),
  bmeSensor->getHumSensorData(),
  bmeSensor->getPressSensorData(),
  veml6040Sensor->getLuxSensorData(),
  veml6075Sensor->getIndexSensorData()) ;

  lightPage->setSensorData( veml6040Sensor->getRedSensorData(),
  veml6040Sensor->getGreenSensorData(),
  veml6040Sensor->getBlueSensorData(),
  veml6040Sensor->getLuxSensorData(),
  veml6040Sensor->getColorTempSensorData()) ;

  gasesPage->setSensorData(mics6814Sensor->getNH3SensorData(),
  mics6814Sensor->getCOSensorData(),
  mics6814Sensor->getNO2SensorData(),
  mics6814Sensor->getC3H8SensorData(),
  mics6814Sensor->getC4H10SensorData(),
  mics6814Sensor->getCH4SensorData(),
  mics6814Sensor->getH2SensorData(),
  mics6814Sensor->getC2H5OHSensorData(),
  ccs811Sensor->getCO2SensorData(),
  ccs811Sensor->getVOCSensorData()

  ) ;

  distancePage->setSensorData(vl53l0xSensor->getDistanceSensorData()) ;
  temperaturePage->setSensorData(mlx90614Sensor->getTempSensorData()) ;

  orientationPage->setSensorData(
    bno055Sensor->getRotationSensorData(), 
    bno055Sensor->getRollSensorData(),
    bno055Sensor->getPitchSensorData()
     ) ;

}
void displayUI()
{
  if ( currentPage >= 0)
  {
    pageList[currentPage]->draw() ;
  }
}

void setup()
{
  Serial.begin(115200) ;
  GO.begin();
  delay(200);

  Serial.println("Boot");
  GO.Speaker.setVolume(11);
  GO.Speaker.update();

  GO.lcd.setTextSize(2);
  GO.lcd.setTextColor(WHITE,BLACK);

  if(!SPIFFS.begin()){
    Serial.println("SPIFFS Mount Failed");
    return;
  }

  GO.lcd.drawJpgFile(SPIFFS, "/Init.jpg", 0, 0, 320, 240, 0, 0, JPEG_DIV_NONE) ;

  GO.lcd.setTextSize(3);
  GO.lcd.setTextColor(CYAN,BLACK);
  GO.lcd.drawString("INITIALIZING", 50, 100) ;

//  Wire.setClock(100000)  ;
  Wire.begin(SDA, SCK);

  delay(40) ;
  Serial.println("INIT Sensors") ;

  for ( int i = 0 ; i < (sizeof ( sensorlist) / sizeof (Sensor)) ; ++i)
  {
    Serial.printf("Init Sensor %d\n", i) ;
    sensorlist[i]->begin() ;
    Serial.printf("Init Sensor %d INITIALIZED\n", i) ;

  }

  delay(40) ;

  initPages() ;


  GO.lcd.drawJpgFile(SPIFFS, "/Init.jpg", 0, 0, 320, 240, 0, 0, JPEG_DIV_NONE) ;

  GO.lcd.setTextSize(3);
  GO.lcd.setTextColor(CYAN,BLACK);
  GO.lcd.drawString("INIT COMPLETE", 50, 100) ;


//  pageList[currentPage]->init() ;
}
void loop()
{

  for ( int i = 0 ; i < (sizeof ( sensorlist) / sizeof (Sensor)) ; ++i)
  {
    sensorlist[i]->update() ;
  }

  GO.BtnB.read() ;
  GO.BtnA.read() ;

  if ( GO.BtnA.isPressed() == 1)
  {

    currentPage++ ;
    if (currentPage == pages)
    {
      currentPage = 0 ;
    }
    pageList[currentPage]->init() ;
  }

  if ( GO.BtnB.isPressed() == 1)
  {
    currentPage-- ;
    if (currentPage < 0)
    {
      currentPage = pages-1 ;
    }
    pageList[currentPage]->init() ;
  }

  displayUI();
  delay(300) ;
}
