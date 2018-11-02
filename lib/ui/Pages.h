#ifndef __Page__
#define __Page__

#include "UIComponents.h"

class Page  {

    public:
      virtual void draw() = 0;
      virtual void init() = 0 ;
      virtual void buttonsPressed( bool menu, bool volume, bool select, bool start) {} ;
    private:
};

class BlankPage : public Page  {

    public:
      virtual void init() ;
      virtual void draw() ;
    private:
};


class AmbientPage : public Page  {

    public:
      virtual void init() ;
      virtual void draw() ;
      void setSensorData(SensorData *tempSensorData,
                         SensorData *humSensorData,
                         SensorData *pressSensorData,
                         SensorData *luxSensorData,
                         SensorData *uvSensorData
                  ) ;
    private:
      SensorData *tempSensorData;
      SensorData *humSensorData;
      SensorData *pressSensorData;
      SensorData *luxSensorData;
      SensorData *uvSensorData;

      UIComponent **components ;

};



class LightPage : public Page  {

    public:
      virtual void init() ;
      virtual void draw() ;

      void setSensorData(SensorData *redSensorData,
                         SensorData *greenSensorData,
                         SensorData *blueSensorData,
                         SensorData *luxSensorData,
                         SensorData *colorTempSensorData
                  ) ;
    private:
      SensorData *redSensorData;
      SensorData *greenSensorData;
      SensorData *blueSensorData;
      SensorData *luxSensorData;
      SensorData *colorTempSensorData;

      UIComponent **components ;

};


class GasesPage : public Page  {

    public:
      virtual void init() ;
      virtual void draw() ;

      void setSensorData(SensorData *nh3Data ,
      SensorData *coData ,
      SensorData *no2Data ,
      SensorData *c3h8Data ,
      SensorData *c4h10Data ,
      SensorData *ch4Data ,
      SensorData *h2Data ,
      SensorData *c2h5ohData ,
      SensorData *co2Data ,
      SensorData *vocData 
                  ) ;
    private:
      SensorData *nh3Data ;
      SensorData *coData ;
      SensorData *no2Data ;
      SensorData *c3h8Data ;
      SensorData *c4h10Data ;
      SensorData *ch4Data ;
      SensorData *h2Data ;
      SensorData *c2h5ohData ;
      SensorData *co2Data ;
      SensorData *vocData ;

      UIComponent **components ;

};






class DistancePage : public Page  {

    public:
      virtual void init() ;
      virtual void draw() ;

      void setSensorData(SensorData *distanceData ) ;
    private:
      SensorData *distanceData ;

      UIComponent **components ;

};

class TemperaturePage : public Page  {

    public:
      virtual void init() ;
      virtual void draw() ;

      void setSensorData(SensorData *temperatureData ) ;
    private:
      SensorData *temperatureData ;

      UIComponent **components ;

};


class OrientationPage : public Page  {

    public:
      virtual void init() ;
      virtual void draw() ;

      void setSensorData(SensorData *yawData,SensorData *rollData,SensorData *pitchData ) ;
    private:
      SensorData *yawData ;
      SensorData *rollData ;
      SensorData *pitchData ;
      double lastRoll = 0 ;
      double lastPitch = 0 ;

      Text *rollText ;
      Text *pitchText ;
      Text *yawText ;

};

class AccelerationPage : public Page  {

    public:
      virtual void init() ;
      virtual void draw() ;
	  virtual void buttonsPressed( bool menu, bool volume, bool select, bool start) ;

      void setSensorData( SensorData *accelX ,
                          SensorData *accelY ,
                          SensorData *accelZ 
                  ) ;

    private:
      SensorData *accelX ;
      SensorData *accelY ;
      SensorData *accelZ ;
      SensorData *accelXMaxNeg ;
      SensorData *accelYMaxNeg ;
      SensorData *accelZMaxNeg ;
      SensorData *accelXMaxPos ;
      SensorData *accelYMaxPos ;
      SensorData *accelZMaxPos ;

      Text *accelXText ;
      Text *accelYText ;
      Text *accelZText ;
      Text *accelXMaxNegText ;
      Text *accelYMaxNegText ;
      Text *accelZMaxNegText ;
      Text *accelXMaxPosText ;
      Text *accelYMaxPosText ;
      Text *accelZMaxPosText ;

};

#endif
