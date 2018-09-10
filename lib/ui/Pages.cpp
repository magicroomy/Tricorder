#include "UIComponents.h"
#include "Pages.h"
#include <odroid_go.h>
#include "Arduino.h"

// --------------------------------------------------------------------

void Page::draw()
{
  for ( int i = 0 ; i < compCount ; ++i )
  {
    components[i]->draw() ;
  }
}

void Page::setComponents(UIComponent **components, int compCount)
{
  Serial.printf("Set Page Components %X  %X\n", components, components[0]) ;
  this->components = components ;
  this->compCount = compCount ;
}


// --------------------------------------------------------------------

void BlankPage::init()
{
  Serial.println("INIT BLANK PAGE") ;
  GO.lcd.clear();
}
