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
    void move_Joint_of_Finger2and3_sim_until ( Joint jointF2, Joint jointF3, int angle_desired );
    void move_Joint_of_Fingeri_until(Joint joint, Finger finger, int angle_desired);
    void move_twoJoints_of_Fingeri_until(Joint joint1, Joint joint2, Finger finger, int angle_desired);
    void move_allJoints_of_Fingeri_until(Finger finger, int angle_desired);
    void Strech_Hand();
    
    
    void lateralPowerGrasping();
    void lateralPrecisionGrasping();
    void cylindricalPowerGrasping();
    void cylindricalPrecisionGrasping();
    void sphericalPowerGrasping();
    void sphericalPrecisionGrasping();
    
};

#endif
