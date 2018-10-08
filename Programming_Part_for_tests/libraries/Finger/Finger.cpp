
#include "Arduino.h"
#include "Joint.h"
#include "Finger.h"
#include "Motor.h"



Finger::Finger( Joint _JointMCP, Joint _JointPIP, Joint _JointDIP, Motor Motor): 
  JointMCP(_JointMCP),
  JointPIP(_JointPIP),
  JointDIP(_JointDIP), 
  motor(Motor)
{}


void Finger::Finger_Underactuated(){
    JointMCP.free_Joint();
    JointPIP.free_Joint();
    JointDIP.free_Joint();
}

void Finger::Finger_ArretAll(){
    JointMCP.lock_Joint();
    JointPIP.lock_Joint();
    JointDIP.lock_Joint();
}

void Finger::Finger_free_DIP_PIP(){
    JointMCP.lock_Joint();
    JointPIP.free_Joint();
    JointDIP.free_Joint();
}
void Finger::Finger_free_PIP_MCP(){
    JointMCP.free_Joint();
    JointPIP.free_Joint();
    JointDIP.lock_Joint();
} 
void Finger::Finger_free_MCP(){
    JointMCP.free_Joint();
    JointPIP.lock_Joint();
    JointDIP.lock_Joint();
}
void Finger::Finger_free_PIP(){
    JointMCP.lock_Joint();
    JointPIP.free_Joint();
    JointDIP.lock_Joint();
}
void Finger::Finger_free_DIP(){
    JointMCP.lock_Joint();
    JointPIP.lock_Joint();
    JointDIP.free_Joint();
}



void Finger::move_oneJoint_until( Joint joint, int desired_angle){


  if (&joint==&JointMCP) {
      Finger_free_MCP();
  }else if(&joint==&JointPIP){
      Finger_free_PIP();
  }else if(&joint==&JointDIP){
      Finger_free_DIP();
  }
  
  motor.drive_Motor_until ( desired_angle, joint);
  joint.lock_Joint();
}


void Finger::move_allJoints_until(int desired_angle){
  Finger_Underactuated();
  motor.drive_Motor_until (desired_angle, JointMCP, JointPIP, JointDIP);
  Finger_ArretAll();
}

void Finger::move_twoJoints_until(Joint joint1, Joint joint2, int desired_angle){
   if( &joint1 !=&JointMCP && &joint2 !=&JointMCP){
    Finger_free_DIP_PIP();
   }else if (&joint1 != &JointDIP && &joint2 !=&JointDIP){
    Finger_free_PIP_MCP();
   }else {
    false;
   }
   motor.drive_Motor_until ( desired_angle, joint1, joint2);
   Finger_ArretAll();
   
}

  
