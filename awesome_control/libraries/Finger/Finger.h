#ifndef Finger_h
#define Finger_h

#include "Arduino.h"
#include "Joint.h"
#include "Motor.h"


class Finger
{
  public:
    Joint JointMCP;
    Joint JointPIP;
    Joint JointDIP;
    Motor motor;
    
  public:
    Finger (Joint _JointMCP, Joint _JointPIP, Joint _JointDIP, Motor Motor);
    void Finger_unlockAll(); //all Joints free
    void Finger_lockAll(); //all Joints Fixed
    
    void open_Finger(int velocity); // openFingerunderactuated
    void move_oneJoint_until( Joint joint, int desired_angle); 
    void move_oneJoint_until_S(Joint joint, int velocity);
   
};

#endif
