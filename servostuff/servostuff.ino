#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <Servo.h>

/* Returns the IMU data as both a euler angles and quaternions as the WebSerial
   3D Model viewer at https://adafruit-3dmodel-viewer.glitch.me/ expects.
 
   This driver uses the Adafruit unified sensor library (Adafruit_Sensor),
   which provides a common 'type' for sensor data and some helper functions.

   To use this driver you will also need to download the Adafruit_Sensor
   library and include it in your libraries folder.

   You should also assign a unique ID to this sensor for use with
   the Adafruit Sensor API so that you can identify this particular
   sensor in any data logs, etc.  To assign a unique ID, simply
   provide an appropriate value in the constructor below (12345
   is used by default in this example).

   Connections
   ===========
   Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VDD to 3.3-5V DC
   Connect GROUND to common ground

   History
   =======
   2020/JUN/01  - First release (Melissa LeBlanc-Williams)
*/

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (5)

// Check I2C device address and correct line below (by default address is 0x29 or 0x28)
//                                   id, address
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);


/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
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
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
   
  delay(1000);

  /* Use external crystal for better accuracy */
  bno.setExtCrystalUse(true);
   
  rollServo.attach(6);
  pitchServo.attach(5);
  servo3.attach(3);


 
}

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/
void loop(void)
{
  /* Get a new sensor event */
  sensors_event_t event;
  bno.getEvent(&event);

  /* Board layout:
         +----------+
         |         *| RST   PITCH  ROLL  HEADING
     ADR |*        *| SCL
     INT |*        *| SDA     ^            /->
     PS1 |*        *| GND     |            |
     PS0 |*        *| 3VO     Y    Z-->    \-X
         |         *| VIN
         +----------+
  */




  pitch = (int)event.orientation.z;
  roll = (int)event.orientation.y;

  newPitch = map(pitch,-180,180,180,0);
  newRoll=map(roll,-180,180,0,180);

  pitchServo.write(newPitch);
  rollServo.write(newRoll);


  delay(BNO055_SAMPLERATE_DELAY_MS);
}
