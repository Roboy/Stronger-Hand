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
    void Finger_Underactuated(); //all Joints free
    void Finger_ArretAll(); //all Joints Fixed
    void Finger_free_DIP_PIP(); // MCP_locked
                            //PIP_locked doesn't exsist
    void Finger_free_PIP_MCP(); //DIP_locked
    void Finger_free_MCP();
    void Finger_free_PIP();
    void Finger_free_DIP();

    void move_oneJoint_until( Joint joint, int desired_angle);
    void move_allJoints_until(int desired_angle);
    void move_twoJoints_until(Joint joint1, Joint joint2, int desired_angle);
};

#endif
