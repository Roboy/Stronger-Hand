

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

void Greifer::lock_all()
{
  Finger1.JointMCP.lock_Joint(255);
  Finger1.JointPIP.lock_Joint(255);
  Finger1.JointDIP.lock_Joint(255);
  
  Finger2.JointMCP.lock_Joint(255);
  Finger2.JointPIP.lock_Joint(255);
  Finger2.JointDIP.lock_Joint(255);
  
  Finger3.JointMCP.lock_Joint(255);
  Finger3.JointPIP.lock_Joint(255);
  Finger3.JointDIP.lock_Joint(255);
  
}

void Greifer::unlock_all()
{
  Finger1.JointMCP.lock_Joint(0);
  Finger1.JointPIP.lock_Joint(0);
  Finger1.JointDIP.lock_Joint(0);
  
  Finger2.JointMCP.lock_Joint(0);
  Finger2.JointPIP.lock_Joint(0);
  Finger2.JointDIP.lock_Joint(0);
  
  Finger3.JointMCP.lock_Joint(0);
  Finger3.JointPIP.lock_Joint(0);
  Finger3.JointDIP.lock_Joint(0);
  
}


void Greifer::Strech_Hand(int velocity)
{ 
  float p1MCP=Finger1.JointMCP.get_Joint_angle();
  float p1PIP=Finger1.JointPIP.get_Joint_angle();
  float p1DIP=Finger1.JointDIP.get_Joint_angle();

  float p2MCP=Finger2.JointMCP.get_Joint_angle();
  float p2PIP=Finger2.JointPIP.get_Joint_angle();
  float p2DIP=Finger2.JointDIP.get_Joint_angle();

  float p3MCP=Finger3.JointMCP.get_Joint_angle();
  float p3PIP=Finger3.JointPIP.get_Joint_angle();
  float p3DIP=Finger3.JointDIP.get_Joint_angle();

  unlock_all();

  while( p1MCP>0 || p1PIP>0 || p1DIP>0 || p2MCP>0 || p2PIP>0 || p2DIP>0 || p3MCP>0 || p3PIP>0 || p3DIP>0){

    if( p1MCP>0 || p1PIP>0 || p1DIP>0)
    { 
      Finger1.motor.drive_Motor(velocity);
      p1MCP=Finger1.JointMCP.get_Joint_angle();
      p1PIP=Finger1.JointPIP.get_Joint_angle();
      p1DIP=Finger1.JointDIP.get_Joint_angle();
    }

    if( p2MCP>0 || p2PIP>0 || p2DIP>0 || p3MCP>0 || p3PIP>0 || p3DIP>0)
    {
      Finger2.motor.drive_Motor(velocity);
      p2MCP=Finger2.JointMCP.get_Joint_angle();
      p2PIP=Finger2.JointPIP.get_Joint_angle();
      p2DIP=Finger2.JointDIP.get_Joint_angle();
  
      p3MCP=Finger3.JointMCP.get_Joint_angle();
      p3PIP=Finger3.JointPIP.get_Joint_angle();
      p3DIP=Finger3.JointDIP.get_Joint_angle();
    } 
  }
  lock_all();
}


void Greifer::move_all_Finger_until(Joint jointF1, Joint jointF2, Joint jointF3, int angle1, int angle2, int angle3, int velocity){

      
      lock_all();

      jointF1.lock_Joint(0);
      jointF2.lock_Joint(0);
      jointF3.lock_Joint(0);

      float a1=jointF1.get_Joint_angle();
      float a2=jointF2.get_Joint_angle();
      float a3=jointF3.get_Joint_angle();

      while( a1 != angle1 || a2 != angle2 || a3 != angle3){

        if (a1!= angle1){
          Finger1.motor.drive_Motor(velocity);
          a1=jointF1.get_Joint_angle();
        }else{
          jointF1.lock_Joint(255);
          Finger1.motor.drive_Motor(95);
         }

        if (a2 != angle2 || a3 != angle3){
          if (a2 == angle2){
            jointF1.lock_Joint(255);
          }

          if(a3 == angle3){
            jointF1.lock_Joint(255);
          }
          Finger2.motor.drive_Motor(velocity);
          a2=jointF2.get_Joint_angle();
          a3=jointF3.get_Joint_angle();   
        }else
          {
          Finger1.motor.drive_Motor(95);
          Finger2.motor.drive_Motor(95);
          }
      }
      Finger1.motor.drive_Motor(95);
      Finger2.motor.drive_Motor(95);
      jointF1.lock_Joint(255);
      jointF2.lock_Joint(255);
      jointF3.lock_Joint(255); 
}


void Greifer::move_Finger1and_Finger2oder3_until(Joint jointF1, Joint jointF2oderF3, int angle1, int angle2oder3){ //only for Finger 2 and 3 
      
      lock_all();

      jointF1.lock_Joint(0);
      jointF2oderF3.lock_Joint(0);

      float a1=jointF1.get_Joint_angle();
      float a2=jointF2oderF3.get_Joint_angle();
      int velocity1;
      int velocity2;

      if(a1<angle1){
        velocity1=100;
      }else
        {
          velocity1=89;
        }

      if(a2<angle2oder3){
        velocity2=100;
      }else
        {
          velocity2=89;
        }
    

      while( a1 != angle1 || a2 != angle2oder3){

        if (a1!=angle1){
          Finger1.motor.drive_Motor(velocity1);
          a1=jointF1.get_Joint_angle();
        }else{
          jointF1.lock_Joint(255);
          Finger1.motor.drive_Motor(95);
         }

        if (a2 != angle2oder3){
          Finger2.motor.drive_Motor(velocity2);
          a2=jointF2oderF3.get_Joint_angle();
        }else{
          jointF2oderF3.lock_Joint(255);
          Finger2.motor.drive_Motor(95);
         }
       }
      jointF1.lock_Joint(255);
      jointF2oderF3.lock_Joint(255);
      Finger1.motor.drive_Motor(95);
      Finger2.motor.drive_Motor(95);
}


void Greifer::move_Finger2oder3_until(Joint joint, int angle_desired){

      Finger2.Finger_lockAll();
      Finger3.Finger_lockAll();

      joint.lock_Joint(0);

      float a=joint.get_Joint_angle();
      int velocity;
      

      if(a<angle_desired){
        velocity=100;
      }else
        {
          velocity=89;
        }

      while( a != angle_desired){

          Finger2.motor.drive_Motor(velocity);
          a=joint.get_Joint_angle();
      }
      joint.lock_Joint(255);
      Finger2.motor.drive_Motor(95);
}




void Greifer::move_all_Finger_until_S(Joint jointF1, Joint jointF2, Joint jointF3, int velocity){

      
      lock_all();

      jointF1.lock_Joint(0);
      jointF2.lock_Joint(0);
      jointF3.lock_Joint(0);

      Serial.println( "for Stop write: S");
      int a=1;

      while (a=1)
      { 
        if (Serial.available())
        {
          if(Serial.read()=='S')
          {
            break;
          }
        }
        Finger1.motor.drive_Motor(velocity);
        Finger2.motor.drive_Motor(velocity);
      }
      Finger1.motor.drive_Motor(95);
      Finger2.motor.drive_Motor(95);
      jointF1.lock_Joint(255);
      jointF2.lock_Joint(255);
      jointF3.lock_Joint(255); 
}


void Greifer::move_Finger1and_Finger2oder3_until_S(Joint jointF1, Joint jointF2oderF3, int velocity){ //only for Finger 2 and 3 
      
      lock_all();

      jointF1.lock_Joint(0);
      jointF2oderF3.lock_Joint(0);

      Serial.println( "for Stop write: S");
      int a=1;

      while (a=1)
      { 
        if (Serial.available())
        {
          if(Serial.read()=='S')
          {
            break;
          }
        }
        Finger1.motor.drive_Motor(velocity);
        Finger2.motor.drive_Motor(velocity);
      }
      Finger1.motor.drive_Motor(95);
      Finger2.motor.drive_Motor(95);
      jointF1.lock_Joint(255);
      jointF2oderF3.lock_Joint(255);
}



void Greifer::move_Finger2oder3_until_S(Joint joint, int velocity){
      
      lock_all();
      joint.lock_Joint(0);

      Serial.println( "for Stop write: S");
      int a=1;

      while (a=1)
      { 
        if (Serial.available())
        {
          if(Serial.read()=='S')
          {
            break;
          }
        }
        
        Finger2.motor.drive_Motor(velocity);
      }
      Finger2.motor.drive_Motor(95);
      joint.lock_Joint(255);
  
}





void Greifer::Close_Hand(int velocity){
  move_all_Finger_until(Finger1.JointMCP, Finger2.JointMCP, Finger3.JointMCP, 45, 45, 45, velocity);
  move_all_Finger_until(Finger1.JointPIP, Finger2.JointPIP, Finger3.JointPIP, 45, 45, 45, velocity);
  move_all_Finger_until(Finger1.JointDIP, Finger2.JointDIP, Finger3.JointDIP, 45, 45, 45, velocity); 
}
