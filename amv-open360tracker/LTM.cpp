#include "config.h"

#ifdef LTM
#include "telemetry.h"
#include <avr/io.h>

//bool HAS_FIX=false;

//
#define LTM_HEADER_START1 0x24 //$
#define LTM_HEADER_START2 0x54 //T
#define LTM_GFRAME 0x47 //G Frame

#define LTM_GFRAME_LENGTH 18
/*#define LIGHTTELEMETRY_AFRAMELENGTH 10
#define LIGHTTELEMETRY_SFRAMELENGTH 11
#define LIGHTTELEMETRY_OFRAMELENGTH 18*/

// Enum machine states
enum LtmDataState {
    IDLE,
    STATE_START1,
    STATE_START2,
    STATE_MSGTYPE,
    STATE_DATA
  };

//
static uint8_t LTM_Buffer[LTM_GFRAME_LENGTH-4];
static uint8_t LTM_Index;
static uint8_t LTM_cmd;
static uint8_t LTM_chk;
static uint8_t LTM_read_index;
static uint8_t LTM_frame_length;
static uint8_t dataState = IDLE;
  
//data needed to buffer

static int16_t alt;
//static int8_t latsign;
//static int8_t lonsign;
static int32_t lat = 0;
static int32_t lon = 0;
static uint8_t sats = 0;

void parseLTM_GFRAME();
uint8_t ltmread_u8();
uint16_t ltmread_u16();
uint32_t ltmread_u32();

int32_t getTargetLat() {
  return lat;
}

int32_t getTargetLon() {
  return lon;
}

int16_t getTargetAlt() {
  return alt;
}

int16_t getSats() {
  return (int16_t)sats;
}

/*int8_t getIndex() {
  return index;
}*/

/*uint16_t getAzimut() {
  return (uint16_t)heading;
}*/

void encodeTargetData(uint8_t c) {

      if (dataState == IDLE && c == '$') {
        dataState = STATE_START1;
      }
      else if (dataState == STATE_START1 && c == 'T') {
        dataState=STATE_START2;
      }
      else if (dataState == STATE_START2) {
        switch (c) {
           case 'G':
             LTM_frame_length = LTM_GFRAME_LENGTH;
             dataState = STATE_MSGTYPE;
             break;
           case 'A':
             /*LTM_frame_length = LIGHTTELEMETRY_AFRAMELENGTH;
             dataState = STATE_MSGTYPE;*/
             dataState=IDLE;
             return;
             break;
           case 'S':
             /*LTM_frame_length = LIGHTTELEMETRY_SFRAMELENGTH;
             dataState = STATE_MSGTYPE;*/
             dataState=IDLE;
             return;
             break;
           default:
             dataState = IDLE;
        }
        LTM_cmd = c;
        LTM_Index=0;
      }
      else if (dataState == STATE_MSGTYPE) {
      if(LTM_Index == 0) {
      LTM_chk = c;
      }
      else {
      LTM_chk ^= c;
      }
        if(LTM_Index == LTM_frame_length-4) {   // received checksum byte
          if(LTM_chk == 0) {
            //printf("Telemetry ok\n");
            /*telemetry_ok = true;
              lastpacketreceived = millis();
              protocol = "LTM";
              ltm_check();*/
            LTM_read_index = 0;
            parseLTM_GFRAME();
              dataState = IDLE;
          }
          else {                                                   // wrong checksum, drop packet
          dataState = IDLE;

          }
        }
        else LTM_Buffer[LTM_Index++]=c;
      }
}

void parseLTM_GFRAME() {


  if (LTM_cmd==LTM_GFRAME)
  {

    lat = (int32_t)ltmread_u32();lat=(int32_t)round(lat/100.0);
    lon = (int32_t)ltmread_u32();lon=(int32_t)round(lon/100.0);
    uint8_t groundspeedms = ltmread_u8();
    int32_t temp_alt = (int32_t)ltmread_u32();//10000000;
    alt=(int)(temp_alt/100.0f);
    uint8_t satsfix = ltmread_u8();
    sats = (satsfix >> 2) & 0xFF;
    uint8_t fix_type = satsfix & 0b00000011;
    //printf("Lat/Lon: %d, %d, Alt: %d, Sats: %d, FixType:%d\n", lat, lon,alt,sats,fix_type);
    if(sats>=5) HAS_FIX = true;

  }
}
uint8_t ltmread_u8()  {
  return LTM_Buffer[LTM_read_index++];
}

uint16_t ltmread_u16() {
  uint16_t t = ltmread_u8();
  t |= (uint16_t)ltmread_u8()<<8;
  return t;
}

uint32_t ltmread_u32() {
  uint32_t t = ltmread_u16();
  t |= (uint32_t)ltmread_u16()<<16;
  return t;
}
#endif
