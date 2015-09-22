#include "inttypes.h"
#include <EEPROM.h>
#include "settings.h"
#include "defines.h"
#include <Arduino.h>

uint8_t EEPROM_DEFAULT[EEPROM_SETTINGS]={
/* 00 */ FMW_VER,
/* 01 */ DEF_S_PID_P,
/* 02 */ DEF_S_PID_I,
/* 03 */ DEF_S_PID_D,
/* 04 */ DEF_S_MAX_PID_ERROR,
/* 05 */ DEF_S_TILT_0,
/* 06 */ DEF_S_TILT_90,
/* 07 */ DEF_S_TILT_EASING,
/* 08 */ DEF_S_TILT_EASING_STEPS, 
/* 09 */ DEF_S_TILT_EASING_MIN_ANGLE, 
/* 10 */ DEF_S_TILT_EASING_MILIS, 
/* 11 */ DEF_S_PAN_0,
/* 12 */ DEF_S_MIN_PAN_SPEED,
/* 13 */ DEF_S_DECLINATION,
/* 14 */ DEF_S_OFFSET,
/* 15 */ DEF_S_LOCAL_GPS,
/* 16 */ DEF_S_GPS_MODEL,
/* 17 */ DEF_S_GPS_BAUDRATE,
/* 18 */ DEF_S_START_TRACKING_DISTANCE,
/* 19 */ DEF_S_LCD_DISPLAY,
/* 20 */ DEF_S_LCD_SIZE_ROW,
/* 21 */ DEF_S_LCD_I2C_ADDR,
/* 22 */ DEF_S_LCD_MODEL,
/* 23 */ DEF_S_BATTERYMONITORING,
/* 24 */ DEF_S_BATTERYMONITORING_RESISTOR_1,
/* 25 */ DEF_S_BATTERYMONITORING_RESISTOR_2,
/* 26 */ DEF_S_BATTERYMONITORING_CORRECTION,
/* 27 */ DEF_S_SERVOTEST,
/* 28 */ DEF_S_CLI
};

uint8_t Settings[EEPROM_SETTINGS];
char *param_names[EEPROM_SETTINGS]={
/* 00 */"check",
/* 01 */"P",
/* 02 */"I",
/* 03 */"D",
/* 04 */"max_pid_error",
/* 05 */"tilt0",
/* 06 */"tilt90",
/* 07 */"easing",
/* 08 */"easing_steps",
/* 09 */"easing_min_angle",
/* 10 */"easing_milis",
/* 11 */"pan0",
/* 12 */"min_pan_speed",
/* 13 */"declination",
/* 14 */"offset",
/* 15 */"gps",
/* 16 */"gps_model",
/* 17 */"gps_bauds",
/* 18 */"start_track_dist",
/* 19 */"lcd",
/* 20 */"lcd_rows",
/* 21 */"lcd_addr",
/* 22 */"lcd_model",
/* 23 */"bat",
/* 24 */"bat_res1",
/* 25 */"bat_res2",
/* 26 */"bat_corr",
/* 27 */"servotest",
/* 28 */"cli"
 };
void writeEEPROM(void)
{
  for(uint8_t en=0;en<EEPROM_SETTINGS;en++){
    EEPROM.write(en+ADDR_OFFSET,Settings[en]);
  } 
  EEPROM.write(0+ADDR_OFFSET,FMW_VER);
}

uint8_t readEEPROM(void)
{
  for(uint8_t en=0;en<EEPROM_SETTINGS;en++){
     Settings[en] = EEPROM.read(en+ADDR_OFFSET);
  }
  return 1;
}
uint8_t checkEEPROM(void)
{
  uint8_t EEPROM_Loaded = EEPROM.read(0+ADDR_OFFSET);
  if (EEPROM_Loaded!=FMW_VER){
    defaultsEEMPROM();
  }
  return 1;
}
void defaultsEEMPROM(void)
{
  for(uint8_t en=0;en<EEPROM_SETTINGS;en++){
      EEPROM.write(en+ADDR_OFFSET,EEPROM_DEFAULT[en]);
  }
  readEEPROM();
}
void dumpSettings(){
  int param_value;
  Serial.println(F("List settings: "));
  for(uint8_t i=1;i<EEPROM_SETTINGS;i++){
    param_value=getParamValue(param_names[i]);
    Serial.print("set ");Serial.print(param_names[i]);Serial.print("=");Serial.println(param_value);
    Serial.flush();
  }
}
uint8_t setParamValue(String param_name,int param_value){
  //Serial.println(param_value);
  uint8_t index;
  uint8_t value;
  int divider;
  if(param_name=="P" || param_name=="I" || param_name=="D" || param_name=="tilt0" || param_name=="tilt90" || param_name=="pan0")
    divider=10;
  else if(param_name=="bat_res1" || param_name=="bat_res2" || param_name=="gps_bauds" || param_name=="offset")
    divider=100;
  else
    divider=1;
  if(param_name=="min_pan_speed" && param_value<0)
    value=abs(param_value)+100;
  else if(param_name=="bat_corr")
    value=param_value*10;
  else
    value=param_value/divider;

  index = getParamIndex(param_name);
  Settings[index]=value;
}
int getParamValue(String param_name){
  uint8_t index = getParamIndex(param_name);
  int value=0;
  uint8_t multiplier;
  
  /*if(param_name=="P" || param_name=="I" || param_name=="D" || param_name=="tilt0" || param_name=="tilt90" || param_name=="pan0")
    multiplier=10;
  else if(param_name=="bat_res1" || param_name=="bat_res2" || param_name=="gps_bauds" || param_name=="offset")
    multiplier=100;
  else
    multiplier=1;*/

  /*if(index>0) {
    if(param_name=="min_pan_speed" && Settings[index]>100)
        value=100-Settings[index];
    else if(param_name=="bat_corr")
        value=(int)((float)Settings[index]/10);
    else   
      value=Settings[index]*multiplier;
  }*/

  multiplier=(index==S_PID_P || index==S_PID_I || index==S_PID_D || index==S_TILT_0 || index==S_TILT_90 || index==S_PAN_0)?10:1;
  multiplier=(index==S_BATTERYMONITORING_RESISTOR_1 || index==S_BATTERYMONITORING_RESISTOR_2 || index==S_GPS_BAUDRATE || index==S_OFFSET)?100:multiplier;
    
  value=(index==S_MIN_PAN_SPEED && Settings[index]>100)?100-Settings[index]:Settings[index]*multiplier;
  value=(index==S_BATTERYMONITORING_CORRECTION)?(int)((float)Settings[index]/10):value;

  //Serial.println(multiplier);
  //Serial.println(value);

  return value;
}
uint8_t getParamIndex(String param_name){
  uint8_t found = false;
  for(uint8_t i=1;i<EEPROM_SETTINGS;i++){
    for(uint8_t x=0;x<param_name.length();x++)
    {
      if(param_names[i][x]==param_name[x])
        found=true;
      else {
        found=false;
        break;
      }
    }
    if(found==true)
      return i;
  }
  Serial.println(F("Parameter not found"));
  return 0;
}

