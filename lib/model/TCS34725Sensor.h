#ifndef __TCS34725SENSOR__
#define __TCS34725SENSOR__

#include <Adafruit_TCS34725.h>
#include "Sensor.h"

#define TCS34725_R_Coef 0.136
#define TCS34725_G_Coef 1.000
#define TCS34725_B_Coef -0.444
#define TCS34725_GA 1.0
#define TCS34725_DF 310.0
#define TCS34725_CT_Coef 3810.0
#define TCS34725_CT_Offset 1391.0

class TCS34725Sensor : public Sensor
{

public:
  TCS34725Sensor();
  virtual void begin();
  virtual void update();
  SensorData *getRedSensorData();
  SensorData *getGreenSensorData();
  SensorData *getBlueSensorData();
  SensorData *getLuxSensorData();
  SensorData *getColorTempSensorData();

private:
  struct tcs_agc
  {
    tcs34725Gain_t ag;
    tcs34725IntegrationTime_t at;
    uint16_t mincnt;
    uint16_t maxcnt;
  };
  static const tcs_agc agc_lst[] ;

//  static const tcs_agc agc_lst[] ;
  uint16_t agc_cur= 0;

  void setGainTime(void);

  Adafruit_TCS34725 tcs;

  boolean isSaturated = 0;
  uint16_t againx, atime, atime_ms;
  uint16_t r, g, b, c;
  uint16_t ir;
  uint16_t r_comp, g_comp, b_comp, c_comp;
  uint16_t saturation, saturation75;
  float cratio, cpl, ct, lux, maxlux;


  SensorData *redData;
  SensorData *greenData;
  SensorData *blueData;
  SensorData *luxData;
  SensorData *colorTempData;
  bool isOK = false;
};
/*
const TCS34725Sensor::tcs_agc TCS34725Sensor::agc_lst[] = {
  {TCS34725_GAIN_60X, TCS34725_INTEGRATIONTIME_700MS, 0, 47566},
  {TCS34725_GAIN_16X, TCS34725_INTEGRATIONTIME_154MS, 3171, 63422},
  {TCS34725_GAIN_4X, TCS34725_INTEGRATIONTIME_154MS, 15855, 63422},
  {TCS34725_GAIN_1X, TCS34725_INTEGRATIONTIME_2_4MS, 248, 0}};
*/
  #endif
