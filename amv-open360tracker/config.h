#ifndef CONFIG_H
#define CONFIG_H

/* Config file
 * created by Samuel Brucksch, edited by Raúl Ortega.
 *
 */
//#define DEBUG

/** PID Values
*
*/
#define P 5000 //5000 //default 2200
#define I 100 //100 //default 280
#define D 100 //1000 //default 20000

/* #### Atmega 2560 ####
 *
 *  If using an APM or Atmega 2560 we do not need softserial, so uncomment if using an atema 2560
 *  
 *  MEGA -> APM & other MEGA Boards
 */
//#define MEGA

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
 *  SERVOTEST
 */
//#define SERVOTEST
#define GPS_TELEMETRY
//#define RVOSD
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
#define TILT_0 1200 // default 1050

/* #### Tilt servo 90° adjustment ####
 *
 *  Enter PWM value of Servo for pointing 90° up
 */
#define TILT_90 1500 // default 2025

/* #### Pan servo 0° adjustment ####
 *
 *  Enter PWM value of Servo for not moving
 */
#define PAN_0 610 // default 1470

/* #### Pan servo minimum required speed ####
 *
 *  If the servo has problems to start a rotation when the speed is slow adjust this value until the tracker moves directly from each position
 */
#define MIN_PAN_SPEED -25 // default 50

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
#define DECLINATION 32 //default 32

/* #### Compass offset ####
 *
 * If you did not mount your compass with the arrow pointing to the front you can set an offset here.
 *
 * Needs to be multiplied by 10 -> 90° = 900
 *
 * Range: 0 ... 3599
 *
 */
#define OFFSET 2700 //default 900

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
#define START_TRACKING_DISTANCE 10 //default 10

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
#define LCD_SIZE_ROW 2 // default 2, tested with 2 and 4
#define LCD_SIZE_COL 16 // default 16, tested with 20 and 16
/*
 * LCD Display I2C ADDRESS
 * Default is 0x27 if uncommented. You'll need a I2C address scanner sketch if you don't know the correct one.
 * If your LCD has a different address descoment this line and change its value.
 */
#define LCD_I2C_ADDR 0x3F // default 0x27

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

#if OFFSET < 0 || OFFSET > 3599
#error "Offset invalid. Must be between 0 and 3599."
#endif

#endif
