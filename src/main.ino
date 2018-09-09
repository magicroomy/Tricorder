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


#define SDA 15
#define SCK 4


ADXL345 accel(ADXL345_ALT);

VEML6040 RGBWSensor;

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

BME280Sensor *bmeSensor = new BME280Sensor() ;
VEML6075Sensor *veml6075Sensor = new VEML6075Sensor() ;
VL53L0XSensor *vl53l0xSensor = new VL53L0XSensor() ;
CCS811Sensor *ccs811Sensor = new CCS811Sensor() ;
MLX90614Sensor *mlx90614Sensor = new MLX90614Sensor() ;

Sensor *sensorlist[] = { bmeSensor, veml6075Sensor, vl53l0xSensor, ccs811Sensor, mlx90614Sensor};

void displayUI()
{
  GO.lcd.clear();
  //GO.lcd.fillRect(0, 80, 200, 50, ILI9341_BLACK);
  GO.lcd.setCursor(0, 0);
  GO.lcd.printf("dist : %.1f\n", distance);
  //  GO.lcd.printf("lux R/G/B/W/CCT/AMB: %f/%f/%f/%f/%f/%f\n", luxR,luxG, luxB, luxW, luxCCT, luxAMB);
  GO.lcd.printf("h/t/p : %.1f/%.1f/%.1f\n", humidity, ambientTemperature,pressure );
  GO.lcd.printf("UV I: %.1f A: %.1f B: %.1f\n",  uvIndex, uvA, uvB);
  GO.lcd.printf("IR : %.1f\n", infrared);
  GO.lcd.printf("CO2 : %.1f  VOC: %.1f\n", co2, voc);
  GO.lcd.printf("gf X: %.1f Y: %.1f Z: %.1f\n", gfX, gfY, gfZ);


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


  GO.lcd.clear();

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


  delay(200) ;

}

void loop()
{
  for ( int i = 0 ; i < (sizeof ( sensorlist) / sizeof (Sensor)) ; ++i)
  {
    Serial.printf("Update Sensor %d\n", i) ;
    sensorlist[i]->update() ;
    Serial.printf("Update Sensor %d DONE\n", i) ;

  }

  Serial.println(F("Read Dist"));

  distance = vl53l0xSensor->getDistanceSensorData()->getValue();
  delay(20) ;
  /*
  luxR = RGBWSensor.getRed();

  luxG = RGBWSensor.getGreen();

  luxB = RGBWSensor.getBlue();

  luxW = RGBWSensor.getWhite();

  luxCCT = RGBWSensor.getCCT();

  luxAMB = RGBWSensor.getAmbientLight();
  */
  delay(20) ;

  Serial.println(F("Read BME280"));

  humidity =  bmeSensor->getTempSensorData()->getValue();
  ambientTemperature = bmeSensor->getHumSensorData()->getValue();
  pressure = bmeSensor->getPressSensorData()->getValue() / 100.0F ;

  delay(20) ;

  Serial.println(F("Read UV"));

  uvA = veml6075Sensor->getUVASensorData()->getValue();
  uvB = veml6075Sensor->getUVBSensorData()->getValue();
  uvIndex = veml6075Sensor->getIndexSensorData()->getValue();

  delay(20) ;

  Serial.println(F("Read VOC"));
  co2 = ccs811Sensor->getCO2SensorData()->getValue();
  voc =ccs811Sensor->getVOCSensorData()->getValue();

  delay(20) ;
  Serial.println(F("Read IR"));

  infrared = mlx90614Sensor->getTempSensorData()->getValue() ;

  Serial.println(F("Read Gyro"));
  if (accel.update()) {
    gfX = accel.getX() ;
    gfY = accel.getY() ;
    gfZ = accel.getZ() ;
  }

  //  infrared = (float) mlx.readObjectTempC();

  Serial.printf("\n\n");

  Serial.printf("dist : %.1f\n", distance);
  Serial.printf("lux R/G/B/W/CCT/AMB: %f/%f/%f/%f/%f/%f\n", luxR,luxG, luxB, luxW, luxCCT, luxAMB);
  Serial.printf("h/t/p : %.1f/%.1f/%.1f\n", humidity, ambientTemperature,pressure );
  Serial.printf("uvA : %.1f uvB : %.1f uvIndex : %.1f\n", uvA, uvB, uvIndex);
  Serial.printf("IR : %.1f\n", infrared);
  Serial.printf("cO2 : %.1f  VOC : %.1f\n", co2, voc);
  Serial.printf("gf X: %.1f Y: %.1f Z: %.1f\n", gfX, gfY, gfZ);

  Serial.printf("\n\n");


  displayUI();
  delay(700) ;
}
