# healthtech-mobility

## Self-Stabilizing System using BNO055 Sensor and Servos

This program implements a self-stabilizing system using a BNO055 sensor and two servos. The program uses a PID control algorithm to adjust the servo angles and keep the sensor upright

### Hardware

#### BNO055 
         +----------+
         |         *| RST   PITCH  ROLL  HEADING
     ADR |*        *| SCL
     INT |*        *| SDA     ^            /->
     PS1 |*        *| GND     |            |
     PS0 |*        *| 3VO     Y    Z-->    \-X
         |         *| VIN
         +----------+


The BNO055 sensor is an integrated 9-axis motion sensor. 

#### Servos

Current servos used only have 180 degrees of motion

#### Fritzing Diagram

TODO

### Software

Basic explanation of algorithm: 

1. Read orientation data from BNO055 
2. Calculate difference between desired orientation angles and current angles 
3. Adjust the servos based on the difference 
4. Repeat


## License

This project is licensed under the GNU Affero General Public License v3.0 - see the LICENSE file for details.
