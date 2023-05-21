#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <Servo.h>

/* Author Sunny Parmar.
*/

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
Servo rollServo, pitchServo, servo3;

int pitch, roll, newPitch, newRoll;
double kp = 1.0; 
double ki = 0.0; // temporarily set to zero 
double kd = 0.0; // temporarily set to zero 
double dt = 0.01; 
unsigned long currentTime;
unsigned long readRate =10.00;

double target_roll = 0.0; 
double target_pitch = 0.0; 

double last_error_roll = 0.0; 
double last_error_pitch = 0.0; 
double integral_error_roll= 0.0;
double integral_error_pitch=0.0;

void setup()
{
  // Initialize the BNO055 sensor
  bno.begin();
  
  // Initialize the servos
  rollServo.attach(6);
  pitchServo.attach(5);
}

void loop()
{
  currentTime = millis();
  if (currentTime % readRate){
    // Read orientation data 
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
    double roll = euler.z();    
    double pitch = euler.y();   
    
    // Calculate the errors for roll and pitch
    double error_roll = target_roll - roll;
    double error_pitch = target_pitch - pitch;
    
    // Calculate the derivative errors for roll and pitch
    double derivative_error_roll = (error_roll - last_error_roll) / dt;
    double derivative_error_pitch = (error_pitch - last_error_pitch) / dt;
    
    // Update the last errors for roll and pitch
    last_error_roll = error_roll;
    last_error_pitch = error_pitch;
    
    // Calculate the integral errors for roll and pitch
    integral_error_roll += error_roll * dt;
    integral_error_pitch += error_pitch * dt;
    
    // Calculate the PID output for each servo
    double output1 = -kp * error_roll + ki * integral_error_roll + kd * derivative_error_roll;
    double output2 = kp * error_pitch + ki * integral_error_pitch + kd * derivative_error_pitch;
  
    
    // Adjust the servo angles based on the PID output
    rollServo.write(output1); 
    pitchServo.write(90 + output2); // 90 is the current ideal position
  }

}

