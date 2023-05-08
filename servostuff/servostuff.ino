#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Servo.h>

/* Author Sunny Parmar.
*/

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (5)
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);
Servo rollServo;
Servo pitchServo;
Servo servo3;
int pitch; 
int roll;
int newPitch;
int newRoll;
void setup(void)
{
  Serial.begin(9600);
  /* Initialise the sensor */
  bno.begin(); 
  delay(1000);
  /* Use external crystal for better accuracy */
  bno.setExtCrystalUse(true);
   
  rollServo.attach(6);
  pitchServo.attach(5);
  servo3.attach(3); 
}

void loop(void)
{
  /* Get a new sensor event */
  sensors_event_t event;
  bno.getEvent(&event);

  pitch = (int)event.orientation.z;
  roll = (int)event.orientation.y;

  newPitch = map(pitch,-360,360,180,0);
  newRoll=map(roll,-360,260,180,0);

  pitchServo.write(newPitch);
  rollServo.write(newRoll);


  delay(BNO055_SAMPLERATE_DELAY_MS);
}
