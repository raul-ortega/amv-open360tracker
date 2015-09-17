#ifndef settings_h
#define settings_h
#include "inttypes.h"
#include <EEPROM.h>
#include "defines.h"
#include <Arduino.h>

enum Protocols {
  P_FRSKY_D,
  P_FRSKY_X,
  P_HOTT,
  P_RVOSD,
  P_MFD,
  P_MAVLINK,
  P_GPS_TELEMETRY
  };
  
enum EasingFuntions {
  F_EASE_OUT_QRT,
  F_EASE_INOUT_QRT,
  F_EASE_OUT_CIRC,
};

enum SupportedLCD {
  LCD_GENERIC_1602,
  LCD_GENERIC_2004,
  LCD_BANGGOOD_SKU166911_1602
};

enum GPSBaudRate {
  BAUD_4800,
  BAUD_9600,
  BAUD_19200,
  BAUD_38400,
  BAUD_57600,
  BAUD_115200  
};

enum Settings_ {
/* 00 */ S_CHECK,
/* 01 */ S_PID_P,
/* 02 */ S_PID_I,
/* 03 */ S_PID_D,
/* 04 */ S_MAX_PID_ERROR,
/* 05 */ S_TILT_0,
/* 06 */ S_TILT_90,
/* 07 */ S_TILT_EASING,
/* 08 */ S_TILT_EASING_STEPS, 
/* 09 */ S_TILT_EASING_MIN_ANGLE, 
/* 10 */ S_TILT_EASING_MILIS, 
/* 11 */ S_PAN_0,
/* 12 */ S_MIN_PAN_SPEED,
/* 13 */ S_DECLINATION,
/* 14 */ S_OFFSET,
/* 15 */ S_LOCAL_GPS,
/* 16 */ S_MTK,
/* 17 */ S_GPS_BAUD_RATE,
/* 18 */ S_START_TRACKING_DISTANCE,
/* 19 */ S_LCD_DISPLAY,
/* 20 */ S_LCD_SIZE_ROW,
/* 21 */ S_LCD_I2C_ADDR,
/* 22 */ S_LCD_MODEL,
/* 23 */ S_BATTERYMONITORING,
/* 24 */ S_BATTERYMONITORING_RESISTOR_1,
/* 25 */ S_BATTERYMONITORING_RESISTOR_2,
/* 26 */ S_BATTERYMONITORING_CORRECTION,
/* 27 */ EEPROM_SETTINGS
};

// Default settings 
#define DEF_S_PID_P                            50 // 50*10 = 500
#define DEF_S_PID_I                            10 // 10*10 = 100
#define DEF_S_PID_D                            10 // 10*10 = 100
#define DEF_S_MAX_PID_ERROR                    10 
#define DEF_S_TILT_0                          150 // 150*10 = 1500 ms
#define DEF_S_TILT_90                         202 // 202*10 = 2020 ms
#define DEF_S_TILT_EASING                       1
#define DEF_S_TILT_EASING_STEPS                10 
#define DEF_S_TILT_EASING_MIN_ANGLE             2 
#define DEF_S_TILT_EASING_MILIS                15
#define DEF_S_PAN_0                           147 // 147*10 = 1470 ms
#define DEF_S_MIN_PAN_SPEED                    50 
#define DEF_S_DECLINATION                       0
#define DEF_S_OFFSET                           90 //  90*10 = 900
#define DEF_S_LOCAL_GPS                         0
#define DEF_S_MTK                               0
#define DEF_S_GPS_BAUD_RATE                    96 // 960*100 = 9600 bauds
#define DEF_S_START_TRACKING_DISTANCE          10
#define DEF_S_LCD_DISPLAY                       1
#define DEF_S_LCD_SIZE_ROW                      2
#define DEF_S_LCD_I2C_ADDR                     39
#define DEF_S_LCD_MODEL          LCD_GENERIC_1602
#define DEF_S_BATTERYMONITORING                 0
#define DEF_S_BATTERYMONITORING_RESISTOR_1    182 // 182*100 = 18200 ohm = 18.2 Kohm
#define DEF_S_BATTERYMONITORING_RESISTOR_2      1 //   1*100 =   100 ohm =  0.1 Kohm
#define DEF_S_BATTERYMONITORING_CORRECTION     11 //   11/10 =   1.1 

#define ADDR_OFFSET 12 // commpass.cpp stores into eeprom 12 integer (2 per axi) after callibration

void writeEEPROM(void);
void readEEPROM(void);
void checkEEPROM(void);
void defaultsEEMPROM(void);
void dumpSettings(void);
uint8_t setParamValue(String param_name,int param_value);
int getParamValue(String param_name);
uint8_t getParamIndex(String parameter);
#endif
