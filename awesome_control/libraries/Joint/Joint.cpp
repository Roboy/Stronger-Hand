
#include "Arduino.h"
#include "Joint.h"
#include "Wire.h"


Joint::Joint (int Magnetpin, int Sensor_ID)
{
  magnetpin=Magnetpin;
  pinMode(magnetpin, OUTPUT);
  analogWrite(magnetpin, 255);
  deviceaddress=Sensor_ID; //0b0001100 for first Sensor
  eeaddress=0x20;
  num= 2;
}


void Joint::lock_Joint (int a){
      analogWrite(magnetpin,a);
}

bool Joint::readMemory(uint8_t deviceaddress, uint8_t eeaddress, byte* rdata, uint8_t num)
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


float Joint::get_Joint_angle() //returns the angle of the sensor at joint j on finger i in degree°
{
    readMemory(deviceaddress, eeaddress, rdata, num); // reads the angle in the pointer rdata
    
    byte l = rdata[0]&15; //  deletes the first 4 bit (not useful data) with 0000 1111 
    float anglebit=(uint16_t)((l<<8)|rdata[1]);
    float angle=anglebit/4096*360; // converts the bitvalue in degree
    return angle;
}
 

//bool Joint::writeMemory(uint8_t deviceaddress, uint8_t eeaddress, byte* wdata)
//{
 // Wire.beginTransmission(deviceaddress);
 // Wire.write(eeaddress); // LSB
 // Wire.write(wdata, 2); // LSB
 // if(Wire.endTransmission(true) != 0){
 //   return false;
 // }
 // return true;
//}
