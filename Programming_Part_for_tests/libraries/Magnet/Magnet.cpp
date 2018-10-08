
#include"Arduino.h"
#include "Magnet.h"


Magnet::Magnet(int8_t _pin)
{
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
  pin = _pin;
}
