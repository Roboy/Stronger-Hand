#include <Wire.h>
#include "Joint.h"
#include "Finger.h"
#include"Greifer.h"
#include "Motor.h"

Joint joint1=Joint(21, 0b0001100);
Motor motor1= Motor(22, A0);
Finger finger1= Finger(joint11, joint12, joint13, motor1);
Finger finger2= Finger(joint21, joint22, joint21, motor2);
Finger finger3= Finger(joint31, joint32, joint33, motor2);
Greifer greifer1 =Greifer(finger1, finger2, finger3);





void setup() {
 Serial.begin(9600);// put your setup code here, to run once:
 
}

void loop() {
  

  
  // put your main code here, to run repeatedly:

}

void test2_Accuracy_Force(){

  int Force;

  for(int i=1, i<45, i++){
    finger1.move_oneJoint_until(joint11, i); 
    Force=motor1.get_Tendon_Force();
    Serial.println(Force);
    }
  
    for(int i=1, i<45, i++){
    finger1.move_oneJoint_until(joint12, i); 
    Force=motor1.get_Tendon_Force();
    Serial.println(Force);
    }
  
    for(int i=1, i<45, i++){
    finger1.move_oneJoint_until(joint13, i); 
    Force=motor1.get_Tendon_Force();
    Serial.println(Force);
    }

}

void test3_Accuracy_Movement(){
  
  int Motorangle;

  //Test Finger 1 unabhängig MCP Joint 
  
  for((int i=1, i<45, i++){
  finger1.move_oneJoint_until(joint11, i);
  Motorangle=motor1.get_Motor_angle();
  Serial.println(Motorangle);
  i=i+1;
  }

  //Test Finger 2 unabhängig MCP Joint
  for((int i=1, i<45, i++){
  greifer1.move_Joint_of_Fingeri_until(joint21, finger2, i);
  Motorangle=motor1.get_Motor_angle();
  Serial.println(Motorangle);
  i=i+1;
  }

  //Test Finger 3 unabhängig MCP Joint
  for((int i=1, i<45, i++){
  greifer1.move_Joint_of_Fingeri_until(joint31, finger3, i);
  Motorangle=motor1.get_Motor_angle();
  Serial.println(Motorangle);
  i=i+1;
  }

  //Test Finger 2 und 3 zusammen MCP Joint
  for((int i=1, i<45, i++){
  greifer1.move_Joint_of_Finger2and3_sim_until ( joint21, joint31, i );
  Motorangle=motor1.get_Motor_angle();
  Serial.println(Motorangle);
  i=i+1;
  }
}

void test4_Check_Force_For_Joint_Locking(int Force){

v=// Formel aus Motorkennlinie aus Motorforce 
finger1.Finger_ArretAll();
motor1.move_Motor (v);

}


void test5_Robustness(int w){

  //w=Wiederholungen; Finger
  for ( int i, i<=w, i++){
    finger1.move_oneJoint_until( joint11, 45);
    finger1.move_oneJoint_until( joint12, 45);
    finger1.move_oneJoint_until( joint13, 45);
  }

  //Hand
  for ( int i, i<=w, i++){
    close_Hand();
  }
  
}


void test6_Kinetik_Finger(){
  finger1.move_oneJoint_until( joint11, 5); //Force Mode!!!
  }
  
void test7_Kinematik_Finger(){

  //closing all Joint from MCP to DIP
  finger1.move_oneJoint_until( joint11, 30);
  finger1.move_oneJoint_until( joint12, 30);
  finger1.move_oneJoint_until( joint13, 30);

  //Open Middle Finger again

  finger1.move_oneJoint_until( joint23, 0);

  
  
  
  finger1.move_allJoints_until(int desired_angle);
  finger1.move_twoJoints_until(Joint joint1, Joint joint2, int desired_angle);
  
  
  }
void test8_Kinetik_Hand(){
  
  greifer1.lateralPowerGrasping();
  greifer1.cylindricalPowerGrasping();
  greifer1.sphericalPowerGrasping();
  
  }
void test9_Kinematik_Hand(){
  greifer1.lateralPrecisionGrasping();
  greifer1.cylindricalPrecisionGrasping();
  greifer1.sphericalPrecisionGrasping();
  
  }
