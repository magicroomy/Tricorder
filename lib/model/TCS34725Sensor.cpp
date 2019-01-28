#include "TCS34725Sensor.h"

TCS34725Sensor::TCS34725Sensor()
{
  redData = new SensorData();
  greenData= new SensorData();
  blueData= new SensorData();
  luxData= new SensorData();
  colorTempData= new SensorData();

}


const TCS34725Sensor::tcs_agc TCS34725Sensor::agc_lst[] = {
  {TCS34725_GAIN_60X, TCS34725_INTEGRATIONTIME_700MS, 0, 47566},
  {TCS34725_GAIN_16X, TCS34725_INTEGRATIONTIME_154MS, 3171, 63422},
  {TCS34725_GAIN_4X, TCS34725_INTEGRATIONTIME_154MS, 15855, 63422},
  {TCS34725_GAIN_1X, TCS34725_INTEGRATIONTIME_2_4MS, 248, 0}};

// Set the gain and integration time
void TCS34725Sensor::setGainTime(void) {
  tcs.setGain(agc_lst[agc_cur].ag);
  tcs.setIntegrationTime(agc_lst[agc_cur].at);
  atime = int(agc_lst[agc_cur].at);
  atime_ms = ((256 - atime) * 2.4);
  switch(agc_lst[agc_cur].ag) {
  case TCS34725_GAIN_1X:
    againx = 1;
    break;
  case TCS34725_GAIN_4X:
    againx = 4;
    break;
  case TCS34725_GAIN_16X:
    againx = 16;
    break;
  case TCS34725_GAIN_60X:
    againx = 60;
    break;
  }
}

// Retrieve data from the sensor and do the calculations
void TCS34725Sensor::update(void) {
  // read the sensor and autorange if necessary
  tcs.getRawData(&r, &g, &b, &c);
  while(1) {
    if (agc_lst[agc_cur].maxcnt && c > agc_lst[agc_cur].maxcnt)
      agc_cur++;
    else if (agc_lst[agc_cur].mincnt && c < agc_lst[agc_cur].mincnt)
      agc_cur--;
    else break;

    setGainTime();
    delay((256 - atime) * 2.4 * 2); // shock absorber
    tcs.getRawData(&r, &g, &b, &c);
    break;
  }

  // DN40 calculations
  ir = (r + g + b > c) ? (r + g + b - c) / 2 : 0;
  r_comp = r - ir;
  g_comp = g - ir;
  b_comp = b - ir;
  c_comp = c - ir;
  cratio = float(ir) / float(c);

  saturation = ((256 - atime) > 63) ? 65535 : 1024 * (256 - atime);
  saturation75 = (atime_ms < 150) ? (saturation - saturation / 4) : saturation;
  isSaturated = (atime_ms < 150 && c > saturation75) ? 1 : 0;
  cpl = (atime_ms * againx) / (TCS34725_GA * TCS34725_DF);
  maxlux = 65535 / (cpl * 3);

  lux = (TCS34725_R_Coef * float(r_comp) + TCS34725_G_Coef * float(g_comp) + TCS34725_B_Coef * float(b_comp)) / cpl;
  ct = TCS34725_CT_Coef * float(b_comp) / float(r_comp) + TCS34725_CT_Offset;

  float rgbSum = (float) (r_comp+ g_comp + b_comp) ;

  float rPercent = ((float) r_comp) / rgbSum * 100;
  float gPercent = ((float) g_comp) / rgbSum * 100;
  float bPercent = ((float) b_comp) / rgbSum * 100;

  redData->setValue(rPercent);
  greenData->setValue(gPercent);
  blueData->setValue(bPercent);




  luxData->setValue(lux);
  colorTempData->setValue(ct);

}


bool TCS34725Sensor::begin()
{
  tcs = Adafruit_TCS34725(agc_lst[agc_cur].at, agc_lst[agc_cur].ag);
  if ((isOK = tcs.begin()))
  {
    setGainTime();
    tcs.setInterrupt(true) ;
  }
  return isOK  ;

}


SensorData *TCS34725Sensor::getRedSensorData()
{
  return redData;
}

SensorData *TCS34725Sensor::getGreenSensorData()
{
  return greenData;
}

SensorData *TCS34725Sensor::getBlueSensorData()
{
  return blueData;
}

SensorData *TCS34725Sensor::getLuxSensorData()
{
  return luxData;
}

SensorData *TCS34725Sensor::getColorTempSensorData()
{
  return colorTempData;
}
