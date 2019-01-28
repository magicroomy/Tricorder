#ifndef __SENSE_BASE__
#define __SENSE_BASE__

class Sensor {
    public:
      virtual bool begin() = 0 ;
      virtual void update() = 0 ;
    private:

};

class SensorData {
    public:
      double getValue() ;
      void setValue(double val) ;
    private:
      double value = 0;
};



#endif
