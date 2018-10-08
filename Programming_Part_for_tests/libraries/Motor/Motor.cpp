#include"Arduino.h"
#include "Joint.h"
#include "Servo.h"
#include"Motor.h"


Motor::Motor(int Motorpin, int Analog_Motorpin)
{
 motorpin=Motorpin; 
 analog_motorpin=Analog_Motorpin;
 analogReference(EXTERNAL); 
 
  servo.attach(motorpin);
  servo_speed = 90; 
}

//float Motor::get_Motor_angle_for_Joint_Angle( Joint joint)
  //{
  //joint.getJoint_angle();
  //delay(10);
  //float analogRead(analog_motorpin);
  //}

void Motor::drive_Motor_until (int angle_desired, Joint joint)
    { 
      
      int diff= angle_desired - joint.getJoint_angle();

      while ( diff!=0){
        
        
          servo.write (90-2*diff); // negative acceleration: if diff = 45° the servo drives with speed 0 (fastest) , if diff = 0° the servo stops
          diff= angle_desired - joint.getJoint_angle();//calculates the difference between the desired angle and the current angle of the joint
          delay(1);   
       }
      servo.write (90);
       
    }


void Motor::drive_Motor_until (int angle_desired, Joint joint1, Joint joint2) {//moves the motor until one common angle 
 
  int diff1= angle_desired - joint1.getJoint_angle();
  int diff2= angle_desired - joint2.getJoint_angle();
  int mindiff=min(diff1,diff2);

      
      while( diff1!=0 || diff2!=0){
          
          servo.write (90-2*mindiff);
          
          diff1= angle_desired - joint1.getJoint_angle();
          diff2= angle_desired - joint2.getJoint_angle();
          
          delay(1);
       

        if(diff1 ==0){
          joint1.lock_Joint();
          mindiff=diff2;
          
        }else if (diff2==0){
          joint2.lock_Joint();
          mindiff=diff1; 
          }else{
           mindiff=min(diff1,diff2);
          }
          
        delay(1);
        
        }
      servo.write (90);

    }

void Motor::drive_Motor_until (int angle_desired, Joint joint1, Joint joint2, Joint joint3){ //moves the motor until one common angle 
 
  int diff1= angle_desired - joint1.getJoint_angle();
  int diff2= angle_desired - joint2.getJoint_angle();
  int diff3= angle_desired - joint3.getJoint_angle();
  int mindiff= min (min (diff1, diff2),diff3);

      
      while( diff1!=0 || diff2!=0 || diff3!=0){
        
          servo. write (90-2*mindiff);
          
          diff1= angle_desired - joint1.getJoint_angle();
          diff2= angle_desired - joint2.getJoint_angle();
          diff3= angle_desired - joint3.getJoint_angle();
         
          delay(1);

        if(diff1 ==0){
          joint1.lock_Joint ();
          if(diff2==0){
            joint2.lock_Joint();
            mindiff=diff3;
          }else if (diff3==0){
            joint3.lock_Joint();
            mindiff=diff2;
          }else{
             mindiff= min (diff2,diff3);
             }
          
        }else if (diff2==0){
          joint2.lock_Joint();
          if (diff3==0){
            joint3.lock_Joint();
            mindiff=diff1;
          }else{
            mindiff= min (diff1,diff3);
            }
          
        }else if (diff3==0){
           joint2.lock_Joint();
           mindiff= min (diff1, diff2);
        }else{
           mindiff= min (min (diff1, diff2),diff3);
           }  
        delay(1);
        
        }

    servo.write (90);

 }
