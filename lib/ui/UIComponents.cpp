#include "UIComponents.h"

#include <Arduino.h>

void BarGraph::draw()
{
  double value = sensorData->getValue() ;
  if ( value < min || value > max )
  {
    return ;
  }

  int newWidth = (int) (factorPixToVal * (value -min) +0.5) ;

  if ( lastWidth < 0)
  {
    GO.lcd.fillRect(x,y,newWidth, height, TFT_BLUE) ;
  }
  else
  {
    if ( lastWidth < newWidth )
    {
      GO.lcd.fillRect(x+lastWidth,y,newWidth-lastWidth, height, TFT_BLUE) ;
    }
    else if ( lastWidth > newWidth )
    {
      GO.lcd.fillRect(x+newWidth,y,lastWidth-newWidth, height, TFT_BLACK) ;

    }
  }
  lastWidth = newWidth ;
}

BarGraph::BarGraph(int x, int y, int width, int height, double min, double max, SensorData *data)
{
  this->x = x ;
  this->y = y ;
  this->width = width ;
  this->height = height ;
  this->min = min ;
  this->max = max ;

  double range = max - min;
  this->factorPixToVal = ((double) width) / range;
  this->sensorData = data ;
}

// -----------------------------------------------------------------------------------------------

void Text::draw()
{
    double value = sensorData->getValue() ;
    char formatted[30]  ;
    sprintf(formatted, format, value) ;
    if ( lastTextLength >= 0)
    {
      GO.lcd.fillRect(x,y,charWidth*lastTextLength, charHeight, bgcolor) ;
    }
    lastTextLength = strlen(formatted) ;
    GO.lcd.setTextColor(fgcolor,bgcolor);
    GO.lcd.drawString(formatted, x,y) ;


}


Text::Text(int x, int y, char *format, uint16_t fgcolor, uint16_t bgcolor, uint8_t textSize, SensorData *data)
{
  this->x = x ;
  this->y = y ;
  this->format = format ;
  this->fgcolor = fgcolor ;
  this->bgcolor = bgcolor ;
  this->textSize = textSize ;
  this->sensorData = data ;
  this->charHeight= 8 * textSize ;
  this->charWidth= 16 * textSize ;
}