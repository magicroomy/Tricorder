#include "WiFiServer.h"
#include "WiFiClientSecure.h"
#include <odroid_go.h>
#include <Wire.h>

#include "veml6040.h"
#include <ADXL345.h>

#include "BME280Sensor.h"
#include "VEML6075Sensor.h"
#include "VL53L0XSensor.h"
#include "CCS811Sensor.h"
#include "MLX90614Sensor.h"
#include "Sensor.h"

#include "Pages.h"
#include "UIComponents.h"

#define SDA 15
#define SCK 4


ADXL345 accel(ADXL345_ALT);
VEML6040 RGBWSensor;
/*
float distance ;
float luxR ;
float luxG ;
float luxB ;
float luxW ;
float luxCCT ;
float luxAMB ;

float humidity;
float ambientTemperature ;
float pressure;
float uvA ;
float uvB ;
float uvIndex ;
float infrared ;
float co2 ;
float voc ;

float gfX ;
float gfY ;
float gfZ ;
*/

BME280Sensor *bmeSensor = new BME280Sensor() ;
VEML6075Sensor *veml6075Sensor = new VEML6075Sensor() ;
VL53L0XSensor *vl53l0xSensor = new VL53L0XSensor() ;
CCS811Sensor *ccs811Sensor = new CCS811Sensor() ;
MLX90614Sensor *mlx90614Sensor = new MLX90614Sensor() ;

Sensor *sensorlist[] = { bmeSensor, veml6075Sensor, vl53l0xSensor, ccs811Sensor, mlx90614Sensor};

BarGraph *distGraph = new BarGraph(0,10,200,20,0,120,vl53l0xSensor->getDistanceSensorData()) ;
Text *distText = new Text(210,25, "%.1lf", WHITE, BLACK, 2 ,vl53l0xSensor->getDistanceSensorData()) ;

BarGraph *irGraph = new BarGraph(0,40,200,20,0,40,mlx90614Sensor->getTempSensorData()) ;
Text *irText = new Text(210,55, "%.1lf", WHITE, BLACK, 2 ,mlx90614Sensor->getTempSensorData()) ;


UIComponent *componentListPage1[] = {distGraph, irGraph, distText, irText} ;

Page *firstPage = new BlankPage() ;
Page *pageList[] = {firstPage} ;

void initPages()
{

  firstPage->setComponents(componentListPage1, sizeof(componentListPage1) / sizeof(UIComponent)) ;
}



void displayUI()
{
  firstPage->draw() ;
/*
  //GO.lcd.fillRect(0, 80, 200, 50, ILI9341_BLACK);
  GO.lcd.setCursor(0, 0);
  GO.lcd.printf("dist : %.1f\n", distance);
  //  GO.lcd.printf("lux R/G/B/W/CCT/AMB: %f/%f/%f/%f/%f/%f\n", luxR,luxG, luxB, luxW, luxCCT, luxAMB);
  GO.lcd.printf("h/t/p : %.1f/%.1f/%.1f\n", humidity, ambientTemperature,pressure );
  GO.lcd.printf("UV I: %.1f A: %.1f B: %.1f\n",  uvIndex, uvA, uvB);
  GO.lcd.printf("IR : %.1f\n", infrared);
  GO.lcd.printf("CO2 : %.1f  VOC: %.1f\n", co2, voc);
  GO.lcd.printf("gf X: %.1f Y: %.1f Z: %.1f\n", gfX, gfY, gfZ);
*/

}

void setup()
{
  Serial.begin(115200) ;
  GO.begin();
  delay(200);

  Serial.println("Boot");
  GO.Speaker.setVolume(11);

  GO.lcd.setTextSize(2);
  GO.lcd.setTextColor(WHITE,BLACK);

  initPages() ;
  firstPage->init() ;


//  GO.lcd.clear();

  Wire.setClock(50000)  ;
  Wire.begin(SDA, SCK);

  delay(40) ;

  // LUX
  /*
  Serial.println("INIT LUX") ;
  if(!RGBWSensor.begin()) {
  Serial.println("ERROR: couldn't detect the sensor");
  while(1){}

  RGBWSensor.setConfiguration(VEML6040_IT_320MS + VEML6040_AF_AUTO + VEML6040_SD_ENABLE);
  */
  delay(40) ;
  Serial.println("INIT Sensors") ;


  for ( int i = 0 ; i < (sizeof ( sensorlist) / sizeof (Sensor)) ; ++i)
  {
    Serial.printf("Init Sensor %d\n", i) ;
    sensorlist[i]->begin() ;
    Serial.printf("Init Sensor %d INITIALIZED\n", i) ;

  }

  delay(40) ;



  // IR

  //mlx.begin();


  Serial.println("INIT GYRO") ;

  byte deviceID = accel.readDeviceID();
  if (deviceID != 0) {
    Serial.printf("0x%2X\n", deviceID);
  } else {
    Serial.println("GYRO Device ID mismatch");
    while(1) {
      delay(100);
    }
  }

  if (!accel.writeRate(ADXL345_RATE_200HZ)) {
    Serial.println("GYRO write rate: failed");
    while(1) {
      delay(100);
    }
  }

  if (!accel.writeRange(ADXL345_RANGE_2G)) {
    Serial.println("GYRO write range: failed");
    while(1) {
      delay(100);
    }
  }

  if (!accel.start()) {
    Serial.println("GYRO start: failed");
    while(1) {
      delay(100);
    }
  }


  delay(100) ;

}

void loop()
{
  for ( int i = 0 ; i < (sizeof ( sensorlist) / sizeof (Sensor)) ; ++i)
  {
    sensorlist[i]->update() ;
  }

  displayUI();
  delay(100) ;
}
