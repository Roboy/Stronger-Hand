#ifndef Motor_h
#define Motor_h

#include "Arduino.h"
#include "Joint.h"
#include "Servo.h"


class Motor
{
  private:
    int motorpin;
    int analog_motorpin;
    int Position;
    int servo_speed;
    Servo servo;
    
  public:
    Motor(int Motorpin, int Analog_Motorpin );
    void drive_Motor_until (int angle_desired, Joint joint);
    void drive_Motor_until (int angle_desired, Joint joint1, Joint joint2);
    void drive_Motor_until (int angle_desired, Joint joint1, Joint joint2, Joint joint3);
    //float Motor::get_Motor_angle_for_Joint_Angle( Joint joint);
    
  
};

#endif
