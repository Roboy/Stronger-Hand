#ifndef Sensor
#define Sensor

#include "Arduino.h"
#include "Wire.h"


class Sensor
{
  public:
    Sensor( uint8_t deviceaddress);
    boolean readMemory;
    
  private:
    byte* rdata;
    uint8_t deviceaddress;
    uint8_t eeaddress;
    uint8_t num;
};

#endif
