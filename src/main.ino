#include "WiFiServer.h"
#include "WiFiClientSecure.h"
#include <odroid_go.h>
#include <Wire.h>

#include <Adafruit_MLX90614.h>
#include <VL53L0X.h>
#include "Adafruit_BME280.h"
#include "Adafruit_CCS811.h"
#include "veml6040.h"
#include <SparkFun_VEML6075_Arduino_Library.h>

#define SDA 15
#define SCK 4

#define BME280_ADD 0x77

VEML6040 RGBWSensor;
VL53L0X distSensor;

Adafruit_CCS811 ccs;

VEML6075 uv; // Create a VEML6075 object

Adafruit_BME280 bme;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

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

void displayUI()
{
  GO.lcd.clear();
  //GO.lcd.fillRect(0, 80, 200, 50, ILI9341_BLACK);
  GO.lcd.setCursor(0, 0);
  GO.lcd.printf("dist : %.1f\n", distance);
  //  GO.lcd.printf("lux R/G/B/W/CCT/AMB: %f/%f/%f/%f/%f/%f\n", luxR,luxG, luxB, luxW, luxCCT, luxAMB);
  GO.lcd.printf("h/t/p : %.1f/%.1f/%.1f\n", humidity, ambientTemperature,pressure );
  GO.lcd.printf("uvA : %.1f uvB : %.1f uvI : %.1f\n", uvA, uvB, uvIndex);
  GO.lcd.printf("IR : %.1f\n", infrared);
  GO.lcd.printf("CO2 : %.1f  VOC: %.1f\n", co2, voc);
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
  Serial.println("INIT BME") ;


  bool status = bme.begin(BME280_ADD);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  delay(40) ;
  // DISTANCE
  Serial.println("INIT DISTANCE") ;

  distSensor.init();
  distSensor.setTimeout(500);
  distSensor.startContinuous(100);


  delay(40) ;
  Serial.println("INIT UV") ;

  if (uv.begin() == false) {
    Serial.println("Unable to communicate with VEML6075.");
    while (1) ;
  }

  delay(40) ;

  Serial.println("INIT VOC") ;
  // VOC
  if(!ccs.begin(  0x5A  )){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }

  //calibrate temperature sensor
  while(!ccs.available());
  float temp = ccs.calculateTemperature();
  ccs.setTempOffset(temp - 25.0);
  ccs.setDriveMode(CCS811_DRIVE_MODE_1SEC) ;

  delay(40) ;


  // IR

  Serial.println("INIT IR") ;

  mlx.begin();


  delay(200) ;

}

void loop()
{
  Serial.println(F("Loop"));

  distance = distSensor.readRangeContinuousMillimeters() / 10;
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


  humidity = bme.readHumidity() ;
  ambientTemperature = bme.readTemperature() ;
  pressure = bme.readPressure() / 100.0F ;

  delay(20) ;

  uvA = uv.uva() ;
  uvB = uv.uvb() ;
  uvIndex = uv.index() ;

  delay(20) ;


  if(ccs.available()){
    uint8_t stat = ccs.readData() ;
    if(!stat){
      ccs.calculateTemperature();
      co2 = ccs.geteCO2();
      voc = ccs.getTVOC();
    }
    else{
      Serial.printf("CSS RET Value %d\n", stat);
      ccs.calculateTemperature();
      co2 = ccs.geteCO2();
      voc = ccs.getTVOC();
    }
  }

  delay(20) ;

  infrared = (float) mlx.readObjectTempC();

  Serial.printf("\n\n");

  Serial.printf("dist : %.1f\n", distance);
  Serial.printf("lux R/G/B/W/CCT/AMB: %f/%f/%f/%f/%f/%f\n", luxR,luxG, luxB, luxW, luxCCT, luxAMB);
  Serial.printf("h/t/p : %.1f/%.1f/%.1f\n", humidity, ambientTemperature,pressure );
  Serial.printf("uvA : %.1f uvB : %.1f uvIndex : %.1f\n", uvA, uvB, uvIndex);
  Serial.printf("IR : %.1f\n", infrared);
  Serial.printf("cO2 : %.1f  VOC : %.1f\n", co2, voc);

  Serial.printf("\n\n");


  displayUI();
  delay(700) ;
}
