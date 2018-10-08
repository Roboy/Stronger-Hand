

#include "Arduino.h"
#include "Joint.h"
#include "Motor.h"
#include "Finger.h"
#include "Greifer.h"

Greifer::Greifer(Finger finger1, Finger finger2, Finger finger3):

    Finger1(finger1),
    Finger2(finger2),
    Finger3(finger3)
{}

void Greifer::move_Joint_of_Finger2and3_sim_until ( Joint jointF2, Joint jointF3, int angle_desired ){ //only for Finger 2 and 3
  

  if( &jointF2==&Finger2.JointMCP && &jointF3==&Finger3.JointMCP){
    Finger2.Finger_free_MCP();
    Finger3.Finger_free_MCP();
    
   }else if (&jointF2 ==&Finger2.JointPIP && &jointF3==&Finger3.JointPIP){
    Finger2.Finger_free_PIP();
    Finger3.Finger_free_PIP();
    
   }else if (&jointF2 ==&Finger2.JointPIP && &jointF3==&Finger3.JointPIP){
    Finger2.Finger_free_DIP();
    Finger3.Finger_free_DIP();
   }else {
    false;
   }
   Finger1.motor.drive_Motor_until (angle_desired, jointF2, jointF3);
  
}

void Greifer::move_Joint_of_Fingeri_until(Joint joint, Finger finger, int angle_desired){ //only for Finger 2 and 3 
  if(&finger==&Finger2){
    Finger3.Finger_ArretAll();
    Finger2.move_oneJoint_until( joint, angle_desired);
  }else if(&finger==&Finger3){
    Finger2.Finger_ArretAll();
    Finger3.move_oneJoint_until( joint, angle_desired);
  }
}


void Greifer::move_twoJoints_of_Fingeri_until(Joint joint1, Joint joint2, Finger finger, int angle_desired){ //only for Finger 2 and 3 
  if(&finger==&Finger2){
    Finger3.Finger_ArretAll();
    Finger2.move_twoJoints_until(joint1, joint2, angle_desired);
  }else if(&finger==&Finger3){
    Finger2.Finger_ArretAll();
    Finger3.move_twoJoints_until(joint1, joint2, angle_desired);
  }
}

void Greifer::move_allJoints_of_Fingeri_until(Finger finger, int angle_desired){ //only for Finger 2 and 3 
  if(&finger==&Finger2){
    Finger3.Finger_ArretAll();
    Finger2.move_allJoints_until(angle_desired);
  }else if(&finger==&Finger3){
    Finger2.Finger_ArretAll();
    Finger3.move_allJoints_until(angle_desired);
  }
}

void Greifer::Strech_Hand(){
  Finger1.move_allJoints_until(45);
  move_allJoints_of_Fingeri_until(Finger2, 45);
  move_allJoints_of_Fingeri_until(Finger3, 45);
  }

void Greifer::lateralPowerGrasping(){

  Strech_Hand();
  int i;

  for( i=0; i< 45; i=i+5){

  Finger1.move_oneJoint_until( Finger1.JointMCP, i);
  move_Joint_of_Finger2and3_sim_until ( Finger2.JointMCP, Finger3.JointMCP ,i);
  
  Finger1.move_oneJoint_until( Finger1.JointPIP, i);
  move_Joint_of_Finger2and3_sim_until( Finger2.JointPIP, Finger3.JointPIP ,i);

  Finger1.move_oneJoint_until( Finger1.JointDIP, i);
  move_Joint_of_Finger2and3_sim_until ( Finger2.JointDIP, Finger3.JointDIP ,i);
  }
}
