#ifndef Motor_h
#define Motor_h

#include "Arduino.h"
#include "Joint.h"
#include <Servo.h>


class Motor
{
  private:
    int motorpin;
    int analog_motorpin;
    Servo servo;
    
  public:
    Motor(int Motorpin, int Analog_Motorpin );
    float get_Motor_angle();
    //int get_Tendon_Force();   
    void drive_Motor(int velocity);
    void drive_Motor_until_Jdegree (int angle_desired, Joint joint);
    void drive_Motor_until_Mdegree(int degree);
    void drive_Motor_for_Jdegree (int angle_desired, Joint joint);
    void drive_Motor_for_Mdegree (int degree);
    void drive_Motor_for_Sek (int Sekunden, int velocity);
    void drive_Motor_until_S(int velocity);
    //void drive_Motor_until_contact(int velocity);
    //void drive_Motor_until_Force(int Force, int velocity);
};

#endif
