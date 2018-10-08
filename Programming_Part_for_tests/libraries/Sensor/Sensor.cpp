#include"Arduino.h"
#include "Sensor.h"


Sensor::Sensor(uint8_t _deviceaddress)
{
    rdata= rdata[2]
    deviceaddress=deviceaddress;
    eeaddress=0x20
    num= 2
}


bool Sensor::readMemory(uint8_t deviceaddress, uint8_t eeaddress, byte* rdata, uint8_t num)
    {
      Wire.beginTransmission(deviceaddress);
      Wire.write(eeaddress);
      if(Wire.endTransmission(false) != 0){ // Restart Line for request
        Wire.endTransmission(true);
        return false;
      }
      
      Wire.requestFrom(deviceaddress, num, (uint8_t) true);
      for(uint8_t i = 0; i < num; i++){
        rdata[i] = Wire.read(); 
      }
      return true;
    }
