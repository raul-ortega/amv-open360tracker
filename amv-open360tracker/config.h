/* Config file
 * created by Samuel Brucksch, edited by Raúl Ortega.
 *
 */
//#define DEBUG

#ifndef CONFIG_H
#define CONFIG_H
/* #### TYPE OF BOARD ####
 *
 *  If using an APM or Atmega 2560 we do not need softserial, so uncomment if using an atema 2560
 *  MEGA -> APM & other MEGA Boards
 *  
 */

#define CRIUS_SE //Default
//#define MEGA
/* #### CONTROLL SYSTEM FOR PAN WITHOUT PIDs (EXPERIMENTAL)####
* 
* If using a slow PAN servo this system could inprove your tracker with a more acurate and fluid movement.
* This system is also more user friendly to set up
*
* Uncomment #define NO_PID_CONTROL for disabling PIDs system and enabling this new system.
*
* MIN_DELTA: is the minimum angle in degrees between the heading of the tracker and the heading of the aircraft.
*   If the current angle is greater than this value, the pan servo will spin.
* MAX_PAN_SPEED: is the maximum value in milliseconds which is necessary to increase the PAN_0 PWM to move the PAN servo.
* MAP_ANGLE: When the angle (in degrees) between the tracker and the aircraft is greater than this value, the MAX_PAN_SPEED is always applied.
*   If the angle is less than this value, the error is mapped to a gradient of PWM pulses between MIN_PAN_SPEED and MAX_PAN_SPEED.
*   
* The PAN servo will spin more and more slowly when is reaching the heading of the aircraft, and will mov as fast as posible when the difference between both headings is big.
*/

//#define NO_PID_CONTROL
#define MIN_DELTA     0.1   // default 0.2
#define MAX_PAN_SPEED 200   // default 200
#define MAP_ANGLE      90   // default 180

/** PID Values
*
* MAX_PID_ERROR is the máximun grades allowed error in the PAN angle calculations.
* If after moving the PAN servo, the difference between reached angle and desired 
* angle is smaller or greater than this value, the angle will be corrected using PIDs.
* 
*/ 
#define P 6500//2500            // default 5000
#define I 0//20             // default 100
#define D 250//200            // default 1000
#define MAX_PID_ERROR 10  // default 10 

/* #### Protocol ####
 *
 *  FRSKY_D, FRSKY_X, HOTT, EXTERNAL
 *
 *  FRSKY_D -> D-Series 
 *  FRSKY_X -> Taranis / XJT 
 *  HOTT -> MX12, MX16 and all other HoTT transmitters with telemetry
 *  RVOSD
 *  MFD -> MFD protocol will not work with local GPS!!!!
 *  MAVLINK -> Mavlink protocol (APM/Pixhawk/...)
 *  GPS_TELEMETRY -> direct NMEA input
 *  LTM -> Light Telemetry 
 *  SERVOTEST
 */
//#define SERVOTEST
//#define GPS_TELEMETRY // Default
//#define MAVLINK
//#define RVOSD
//#define FRSKY_D
//#define FRSKY_X
#define MFD
//#define LTM
/* #### Baud Rate ####
 *
 * baud rate of telemetry input
 * 9600 for FRSKY_D -> D-Series
 * 57600 for FRSKY_X -> Taranis/XJT and MAVLINK
 * 115200 for RVOSD (RVGS)
 * ??? for HoTT
 */
#define BAUD 9600 // default 9600

/* #### Tilt servo 0° adjustment ####
 *
 *  Enter PWM value of Servo for pointing straight forward
 */
#define TILT_0 1125 // default 1050

/* #### Tilt servo 90° adjustment ####
 *
 *  Enter PWM value of Servo for pointing 90° up
 */
#define TILT_90 2100 // default 2025

/* ### Easing effect for tilt movements (EXPERIMENTAL)
 *
 * TILT_EASING_STEPS is the maximun number of steps to reach tilt position using easing functions
 *
 * 0 or 1:   normal use, no easing effect applied, servo will reach tilt position in only 1 step.
 * >1:  servo will move to tilt position in with easing effect.
 * 60 steps ~ 1 second
 * 30 steps ~ 1/2 seconds
 * 15 stips ~ 1/4 seconds
 *
 * TILT_EASING_MIN_ANGLE: Easing is applied if the difference between last and new tilt position is greater than TILT_EASING_MIN_ANGLE grade.
 * TILT_EASING_MILIS: Is the time in miliseconds spend by echa step.
 */
//#define TILT_EASING
#define TILT_EASING_STEPS 10    // default 10
#define TILT_EASING_MIN_ANGLE 2 // default 4
#define TILT_EASING_MILIS 15    //default 15

/*
 * ### Easing ecuations
 *  EASE_OUT_QRT ->  The easing effect is only applied at the end of the movement.
 *  EASE_INOUT_QRT -> The easing effect is applied at the begining and at the end of the movement.
 *  EASE_OUT_CIRC -> The easing out circular effect.
 *  Read more: Easing ecuations by Robert Penner, http://www.gizma.com/easing/
 */
//#define EASE_OUT_QRT    // Easing Out Quart function
//#define EASE_INOUT_QRT  // Easing In Out Quart function
#define EASE_OUT_CIRC     // Easing Out Circular function (Default)

/* #### Pan servo 0° adjustment ####
 *
 *  Enter PWM value of Servo for not moving
 */
#define PAN_0 1528 //620 // default 1470

/* #### Pan servo minimum required speed ####
 *
 *  If the servo has problems to start a rotation when the speed is slow adjust this value until the tracker moves directly from each position
 */
#define MIN_PAN_SPEED 0 // default 50

/* #### Compass declination ####
 *
 * http://magnetic-declination.com/
 * Enter your city and then get the value for Magnetic declination
 * for example [Magnetic declination: 3° 2' EAST]
 *
 * now enter the value in the format DEGREE.MINUTE * 10 -> 3.2 * 10 = 32
 *
 * set to 0 if you cannot find your declination!
 */
 
#define DECLINATION 0 //default 32

/* #### Compass offset ####
 *
 * If you did not mount your compass with the arrow pointing to the front you can set an offset here.
 *
 * Range: 0 ... 359
 *
 */
#define OFFSET 0 //default 0 

/* #### DIY GPS / Fix Type ####
*
* If you use the diy GPS the fix type is transmitted with the satellites on Temp2. The value is calculated like this:
* Num of Sats: 7
* Fix Type: 3
* Value = Sats * 10 + Fix Type = 7*10 + 3 = 73
*
* If you use the native frsky gps or fixtype is not present comment to disable.
*/
//#define DIY_GPS

#ifndef MFD
/* #### Ground GPS ####
 *
 * !!!!!!NOT SUPPORTED YET!!!!!!!
 *
 * needed for ground gps so home does not need to be manually set
 *
 * Types:
 * MTK, UBX
 * UBX not implemented yet
 *
 * does not work when in MFD mode
 */
//#define LOCAL_GPS // default uncommented
//#define MTK
#define GPS_BAUDRATE 9600 //default 9600
#endif

/* #### Tracker Setup ####
 *
 * Start tracking when plane is XXX m away from tracker
 *
 * It is recommended to start tracking only if plane moved a few meters already. Default: 10m
 *
 */
#define START_TRACKING_DISTANCE 1//10 //default 10

/* ### LCD Display ###
 *
 * Uncomment to display data on LCD Display
 *
 * Please choose for the Display Type:
 * I2C
 * SPI
 *
 * LCD Display is required for this.
 *
 *  Requires modified LiquidCrystal library: https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
 *
 */
#define LCD_DISPLAY I2C
// no usar esta línea, es sólo experimental // #define LCD_SIZE_COL 16 // default 16. Not tested 20.
#define LCD_SIZE_ROW 2  // default 2. Not tested with 4.

/*
 * LCD Display I2C ADDRESS
 * Default is 0x27 if uncommented. You'll need a I2C address scanner sketch if you don't know the correct one.
 * If your LCD has a different address descoment this line and change its value.
 */
#define LCD_I2C_ADDR 0x3F //default 0x27

/*
* LCD display bought at en Banggood http://www.banggood.com/IIC-I2C-1602-Blue-Backlight-LCD-Display-Module-For-Arduino-p-950726.html
* Download and install this LiquidCrystal I2C library https://www.dropbox.com/s/e5p9q5tq6sn5m7o/LiquidCrystal_para_LCD_BANGGOOD_SKU166911_I2C.zip?dl=0
* The 1602 is the correct one.
* The default I2C address for this LCD display is 0x3F
*/
#define LCD_BANGGOOD_SKU166911 //default commented

/* ### Battery monitoring ###
 *
 * Uncomment to monitor your Battery
 *
 * Voltage divider is required for this.
 *
 */
//#define BATTERYMONITORING
#ifdef BATTERYMONITORING
//#define BATTERYMONITORING_RESISTOR_1 18000
//#define BATTERYMONITORING_RESISTOR_2 1000
//#define BATTERYMONITORING_CORRECTION 1.0    // default 1.0
#endif

/* #### Do not edit below this line */
#if TILT_0 < 800 || TILT_0 > 2200 || TILT_90 > 2200  || TILT_90 < 800
#error "Tilt servo range invalid. Must be between 800 and 2200."
#endif

#if OFFSET < 0 || OFFSET > 359
#error "Offset invalid. Must be between 0 and 359."
#endif

#endif
