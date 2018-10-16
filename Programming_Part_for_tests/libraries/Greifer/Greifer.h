#ifndef Greifer_h
#define Greifer_h

#include "Arduino.h"
#include "Finger.h"
#include "Joint.h"
#include "Motor.h"

class Greifer
{ public:
    Finger Finger1;
    Finger Finger2;
    Finger Finger3;
    
  public:
    Greifer (Finger _Finger1, Finger _Finger2, Finger _Finger3);
    void move_Joint_of_Finger2and3_sim_until ( Joint jointF2, Joint jointF3, int angle_desired);
    
    void Strech_Hand(int velocity);
    void lock_all();
    void unlock_all();
    void move_all_Finger_until(Joint jointF1, Joint jointF2, Joint jointF3, int angle1, int angle2, int angle3, int velocity);
    void move_Finger1and_Finger2oder3_until(Joint jointF1, Joint jointF2oderF3, int angle1, int angle2oder3);
    void move_Finger2oder3_until(Joint joint, int angle_desired);
    
    void move_all_Finger_until_S(Joint jointF1, Joint jointF2, Joint jointF3, int velocity);
    void move_Finger1and_Finger2oder3_until_S(Joint jointF1, Joint jointF2oderF3, int velocity);
    void move_Finger2oder3_until_S(Joint joint, int velocity);
    void Close_Hand(int velocity);
    
    
};

#endif
