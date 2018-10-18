#include <ros.h>
#include <sensor_msgs/ChannelFloat32.h>
#include <std_msgs/Int8.h>

ros::NodeHandle  nh;

sensor_msgs::ChannelFloat32 channel_msg;
std_msgs::Int8 command_string;
ros::Publisher joint_angles_publisher("/stronger_hand/joints", &channel_msg);
ros::Publisher motor_state_publisher("/stronger_hand/motors", &channel_msg);

#include <Wire.h>
#include "Joint.h"
#include "Motor.h"
#include "Finger.h"
#include "Greifer.h"
Joint joint1_MCP=Joint(4, 0b0001100);
Joint joint1_PIP=Joint(5, 0b0001100);
Joint joint1_DIP=Joint(6, 0b0001100);
Joint joint2_MCP=Joint(7, 0b0001100);
Joint joint2_PIP=Joint(8, 0b0001100);
Joint joint2_DIP=Joint(9, 0b0001100);
Joint joint3_MCP=Joint(10, 0b0001100);
Joint joint3_PIP=Joint(11, 0b0001100);
Joint joint3_DIP=Joint(12,0b0001100);


Motor motor1= Motor(3, A1);
Motor motor2= Motor(2, A0);
Finger finger1= Finger(joint1_MCP, joint1_PIP, joint1_DIP, motor1);
Finger finger2= Finger(joint2_MCP, joint2_PIP, joint2_DIP, motor2);
Finger finger3= Finger(joint3_MCP, joint3_PIP, joint3_DIP, motor2);
Greifer greifer1 =Greifer(finger1, finger2, finger3);

void gripper_commandCB( const std_msgs::Int8& command_msg){
  
  if(command_msg.data == 0){
    finger1.Finger_lockAll();
  }else if(command_msg.data == 1){
    finger2.Finger_lockAll();
  }else if(command_msg.data == 2){
    finger3.Finger_lockAll();
  }else if(command_msg.data == 3){
    finger1.Finger_unlockAll();
  }else if(command_msg.data == 4){
    finger2.Finger_unlockAll();
  }else if(command_msg.data == 5){
    finger3.Finger_unlockAll();
  }
}

ros::Subscriber<std_msgs::Int8> gripper_command("/stronger_hand/command", gripper_commandCB );

void setup() {
  nh.initNode();
  nh.advertise(joint_angles_publisher);
  nh.advertise(motor_state_publisher);
  nh.subscribe(gripper_command);
  channel_msg.values_length = 3;
  pinMode(14, OUTPUT);
  digitalWrite(14, LOW);
}

void loop() {
  channel_msg.name = "finger0";
  
//  channel_msg.values[0] = 0;
//  channel_msg.values[1] = 1;
//  channel_msg.values[2] = 2;
//  joint_angles_publisher.publish(&channel_msg);
  nh.spinOnce();
//  delay(1000);
  
  // put your main code here, to run repeatedly:

}
//
//void open_Finger(int velocity);
//
//  int p1=joint1_MCP.get_Joint_angle;
//  int p2=joint1_PIP.get_Joint_angle;
//  int p3=joint1_DIP.get_Joint_angle;
//
//  while( p1>0 || p2>0 || p3>0){
//    
//    motor1.drive_Motor(velocity);
//    p1=joint1_MCP.get_Joint_angle;
//    p2=joint1_PIP.get_Joint_angle;
//    p3=joint1_DIP.get_Joint_angle; 
//    
//  }
//
//void test1_Accuracy_Force(int velocity){ // velocity has to be super low!! quasi static (100)
//
//  open_Finger(80);
//
//      joint1_MCP.lock_Joint(0);
//      joint2_PIP.lock_Joint(0);
//      joint3_DIP.lock_joint(0);
//
//      int f=motor1.get_Tendon_Force();
//      Serial.println(f);
//      Serial.println("MCPPJoint:");
//      
//
//      for (int i; i<45; i=i+5){
//        
//        motor1.drive_Motor_until_Jdegree(i,joint1_MCP, int velocity);
//        f=motor1.get_Tendon_Force();
//        Serial.println(f);
//      }
//
//      Serial.println("PIPJoint:");
//
//      for (int i; i<45; i++){
//        
//        motor1.drive_Motor_until_Jdegree(i,joint1_PIP, int velocity);
//        f=motor1.get_Tendon_Force();
//        Serial.println(f);
//      }
//      Serial.println("DIPJoint:");
//
//      for (int i; i<45; i++){
//        
//        motor1.drive_Motor_until_Jdegree(i,joint1_DIP, int velocity);
//        f=motor1.get_Tendon_Force();
//        Serial.println(f);
//      }
//
//      
//
//      
//}
//
//void test2_Accuracy_Movement(int velocity, Joint joint){ // Accuracy Test for one Finger and one Joint just for Finger 1!
//
//      open_Finger(80);
//
//      joint1_MCP.lock_Joint(255);
//      joint2_PIP.lock_Joint(255);
//      joint3_DIP.lock_joint(255);
//
//      int m=motor1.get_Motor_angle();
//      Serial.println(m);
//      Serial.println("MCPPJoint:");
//      
//
//      for (int i; i<45; i=i+5){
//        
//        motor1.drive_Motor_until_Jdegree(i,joint1_MCP, int velocity);
//        m=motor1.get_Motor_angle();
//        Serial.println(m);
//      }
//
//      Serial.println("PIPJoint:");
//
//      for (int i; i<45; i++){
//        
//        motor1.drive_Motor_until_Jdegree(i,joint1_PIP, int velocity);
//        m=motor1.get_Motor_angle();
//        Serial.println(m);
//      }
//      Serial.println("DIPJoint:");
//
//      for (int i; i<45; i++){
//        
//        motor1.drive_Motor_until_Jdegree(i,joint1_DIP, int velocity);
//        m=motor1.get_Motor_angle();
//        Serial.println(m);
//      }
//    }
//  
//void test3_Joint_Position_Precision(int angle, Joint joint, int velocity, int Time){
//
//  int a1=millis();
//  int a2=a1+Time;
//  int a=0;
//  int p=joint.get_Joint_angle();
//
//  while(a<a2){
//    if(p>=angle){
//      joint.lock_Joint(255);
//    }
//
//    motor1.drive_Motor(velocity);
//    a=millis();
//    p=joint.get_Joint_angle();
//  }
//
//  return p;
//  
//}
//
//void test4_Check_Force_For_Joint_Locking(int Force){
//
//open_Finger(80);
//
//      joint1_MCP.lock_Joint(255);
//      joint2_PIP.lock_Joint(255);
//      joint3_DIP.lock_joint(255);
//
//      int f=motor.get_Tendon_Force();
//      Serial.println(f);
//      Serial.println("MCPPJoint:");
//      
//
//      for (int i; i<45; i=i+5){
//        
//        motor1.drive_Motor_until_Jdegree(i,joint1_MCP, int velocity);
//        f=motor.get_Tendon_Force();
//        Serial.println(f);
//      }
//
//      Serial.println("PIPJoint:");
//
//      for (int i; i<45; i++){
//        
//        motor1.drive_Motor_until_Jdegree(i,joint1_PIP, int velocity);
//        f=motor.get_Tendon_Force();
//        Serial.println(f);
//      }
//      Serial.println("DIPJoint:");
//
//      for (int i; i<45; i++){
//        
//        motor1.drive_Motor_until_Jdegree(i,joint1_DIP, int velocity);
//        f=motor.get_Tendon_Force();
//        Serial.println(f);
//      }    
//
//
//}
//
//
//void test5_Robustness(int w, int angle){
//  
//
//  //w=Wiederholungen; Finger
//  for ( int i, i<=w, i++){
//    open_Finger(80);
//    finger1.move_oneJoint_until( joint1_MCP, angle);
//    finger1.move_oneJoint_until( joint1_PIP, angle);
//    finger1.move_oneJoint_until( joint1_DIP, angle);
//  }
//
//  //Hand
//  for ( int i, i<=w, i++){
//    Strech_Hand (80);
//    greifer.move_all_Finger_until(finger1.JointMCP, finger2.JointMCP, finger3.JointMCP, angle, angle, angle, 100);
//    greifer.move_all_Finger_until(finger1.JointPIP, finger2.JointPIP, finger3.JointPIP, angle, angle, angle, 100);
//    greifer.move_all_Finger_until(finger1.JointDIP, finger2.JointDIP, finger3.JointDIP, angle, angle, angle, 100);   
//      
//      }
//}
//  
//
//
//void test6_Kinetik_Finger(){
//  int f;
//  
//  open_Finger(80);
//  finger1.move_oneJoint_until( joint1_MCP, 5); //Force Mode!!!
//  f=motor1.get_Tendon_Force();
//  println(f1);
//  
//  }
//  
//void test7_Kinematik_Finger(){
//  int p3;
//  int p2;
//  int p1;
//  
//  open_Finger(80);
//  delay(2000);
//  
//  //lateral Precision
//  finger1.move_oneJoint_until( joint1_MCP, 45);
//
//  open_Finger(80);
//  delay(2000);
//  
//  //lateral Power
//  finger1.move_oneJoint_until( joint1_DIP, 23);
//    
//    
//    p3=joint1_DIP.get_Joint_angle();
//    p2=joint1_PIP.get_Joint_angle();
//
//   for (p2 < 23){
//    finger1.move_oneJoint_until( joint1_PIP,p2+1);
//    finger1.move_oneJoint_until( joint1_DIP,p3-1);
//
//    p3=joint1_DIP.get_Joint_angle();
//    p2=joint1_PIP.get_Joint_angle();
//   }
//
//   
//
//    p2=joint1_PIP.get_Joint_angle();
//    p1=joint1_MCP.get_Joint_angle();
//
//   for (p1 < 23){
//    finger1.move_oneJoint_until( joint1_MCP,p1+1);
//    finger1.move_oneJoint_until( joint1_PIP,p2-1);
//
//    p2=joint1_PIP.get_Joint_angle();
//    p1=joint1_MCP.get_Joint_angle();
//   }
//
//  open_Finger(80);
//  delay(2000);
//  
//  //cylindrical/spherical Precision
//  finger1.move_oneJoint_until( joint1_DIP,45);
//  finger1.move_oneJoint_until( joint1_PIP,45);
//  finger1.move_oneJoint_until( joint1_MCP, "STOP");
//
//  open_Finger(80);
//  delay(2000);
//
//  //cylindrical/spherical Power
//  finger1.move_oneJoint_until( joint1_PIP,22,5);
//  finger1.move_oneJoint_until( joint1_MCP, "STOP");
//  finger1.move_oneJoint_until( joint1_PIP, "STOP");
//}
//
//
//  
//void test8_Kinetik_Hand()
//{
//  greifer1.lateralPowerGrasping();
//  greifer1.cylindricalPowerGrasping();
//  greifer1.sphericalPowerGrasping(); 
//}
//
//void test9_Kinematik_Hand()
//{
//  int p1MCP;
//  int p1PIP;
//  int p1DIP;
//  int p2MCP;
//  int p2PIP;
//  int p2DIP;
//  int p3MCP;
//  int p3PIP;
//  int p3DIP;
//  
//  open_Finger(80);
//  delay(2000);
//  
//  //lateral Precision
//  
//  finger1.move_oneJoint_until( joint1_MCP, 45);
//
//  open_Finger(80);
//  delay(2000);
//  
//  //lateral Power
//  finger1.move_oneJoint_until( joint1_DIP, 23);
//    
//    
//    p3=joint1_DIP.get_Joint_angle();
//    p2=joint1_PIP.get_Joint_angle();
//
//   for (p2 < 23){
//    finger1.move_oneJoint_until( joint1_PIP,p2+1);
//    finger1.move_oneJoint_until( joint1_DIP,p3-1);
//
//    p3=joint1_DIP.get_Joint_angle();
//    p2=joint1_PIP.get_Joint_angle();
//   }
//
//   
//
//    p2=joint1_PIP.get_Joint_angle();
//    p1=joint1_MCP.get_Joint_angle();
//
//   for (p1 < 23){
//    finger1.move_oneJoint_until( joint1_MCP,p1+1);
//    finger1.move_oneJoint_until( joint1_PIP,p2-1);
//
//    p2=joint1_PIP.get_Joint_angle();
//    p1=joint1_MCP.get_Joint_angle();
//   }
//
//  open_Finger(80);
//  delay(2000);
//  
//  //cylindrical/spherical Precision
//  move_all_Finger_until(finger1.JointDIP, finger2.JointDIP, finger3.JointDIP, 45, 45, 45, 100);
//  move_all_Finger_until(finger1.JointPIP, finger2.JointPIP, finger3.JointPIP, 45, 45, 45, 100);
//  move_all_Finger_until(finger1.JointMCP, finger2.JointMCP, finger3.JointMCP, "STOP", "STOP", "STOP", 100);
//  
//
//  open_Finger(80);
//  delay(2000);
//
//  //cylindrical/spherical Power
//  
//  move_all_Finger_until(finger1.JointPIP, finger2.JointPIP, finger3.JointPIP, 22,5, 22,5, 22,5, 100);
//  move_all_Finger_until(finger1.JointDIP, finger2.JointMCP, finger3.JointMCP, "STOP", "STOP", "STOP", 100);
//  move_all_Finger_until(finger1.JointDIP, finger2.JointDIP, finger3.JointDIP, "STOP", "STOP", "STOP", 100);
//  finger1.move_oneJoint_until( joint1_PIP,22,5);
//  finger1.move_oneJoint_until( joint1_MCP, "STOP");
//  finger1.move_oneJoint_until( joint1_PIP, "STOP");
//}
