#ifndef __Page__
#define __Page__

#include "UIComponents.h"

class Page  {

    public:
      void draw();
      virtual void init() = 0 ;
      void setComponents(UIComponent **components, int compCount) ;
    private:
      UIComponent **components ;
      int compCount = 0 ;
};


class BlankPage : public Page  {

    public:
      virtual void init() ;
    private:
};



#endif
