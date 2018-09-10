#ifndef __UIComponents__
#define __UIComponents__

#include "Sensor.h"
#include <odroid_go.h>

class UIComponent  {
    public:
      virtual void draw() = 0;
    private:
};

class BarGraph : public UIComponent  {

    public:
      BarGraph(int x, int y, int width, int height, double min, double max, SensorData *data) ;
      virtual void draw() ;
    private:
      int x, y, width, height;
      double min, max ;
      int lastWidth = -1 ;
      double factorPixToVal;
      SensorData *sensorData ;
};

class Text : public UIComponent  {

    public:
      Text(int x, int y, char *format, uint16_t fgcolor, uint16_t bgcolor, uint8_t textSize, SensorData *data) ;
      virtual void draw() ;
    private:
      int x, y;
      char *format ;
      uint16_t fgcolor, bgcolor ;
      uint8_t textSize ;
      SensorData *sensorData ;
      int16_t lastTextLength= -1 ;
      int16_t charHeight= -1 ;
      int16_t charWidth= -1 ;
};


#endif
