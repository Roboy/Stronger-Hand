#ifndef Magnet
#define Magnet

#include "Arduino.h"

class Magnet
{
  public:
    Magnet(int _pin);
  private:
    int pin;
};

#endif
