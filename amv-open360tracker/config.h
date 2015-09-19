#ifndef CONFIG_H
#define CONFIG_H

/* Config file
 * created by Samuel Brucksch, edited by Raúl Ortega.
 *
 */
//#define DEBUG

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

/*
* LCD display bought at en Banggood http://www.banggood.com/IIC-I2C-1602-Blue-Backlight-LCD-Display-Module-For-Arduino-p-950726.html
* Download and install this LiquidCrystal I2C library https://www.dropbox.com/s/e5p9q5tq6sn5m7o/LiquidCrystal_para_LCD_BANGGOOD_SKU166911_I2C.zip?dl=0
* The 1602 is the correct one.
* The default I2C address for this LCD display is 0x3F
*/
//#define LCD_BANGGOOD_SKU166911 //default commented

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

#endif
