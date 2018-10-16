
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


void Finger::Finger_unlockAll(){
    JointMCP.lock_Joint(0);
    JointPIP.lock_Joint(0);
    JointDIP.lock_Joint(0);
}

void Finger::Finger_lockAll(){
    JointMCP.lock_Joint(255);
    JointPIP.lock_Joint(255);
    JointDIP.lock_Joint(255);
}



void Finger::open_Finger(int velocity)
{
  Finger_unlockAll();
  
  float p1=JointMCP.get_Joint_angle();
  float p2=JointPIP.get_Joint_angle();
  float p3=JointDIP.get_Joint_angle();

  while( p1>0 || p2>0 || p3>0)
  {
    motor.drive_Motor(velocity);
    p1=JointMCP.get_Joint_angle();
    p2=JointPIP.get_Joint_angle();
    p3=JointDIP.get_Joint_angle(); 
    
  }
}



void Finger::move_oneJoint_until( Joint joint, int desired_angle){

  Finger_lockAll();
  joint.lock_Joint(0);
  
  motor.drive_Motor_until_Jdegree (desired_angle, joint);
  joint.lock_Joint(255);
}


void Finger::move_oneJoint_until_S(Joint joint, int velocity)
{
  Finger_lockAll();
  joint.lock_Joint(0);

  motor.drive_Motor_until_S(velocity);
  joint.lock_Joint(255);
}





  
