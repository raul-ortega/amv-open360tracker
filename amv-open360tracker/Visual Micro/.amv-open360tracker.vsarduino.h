/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino Pro or Pro Mini w/ ATmega328 (5V, 16 MHz), Platform=avr, Package=arduino
*/

#define __AVR_ATmega328p__
#define __AVR_ATmega328P__
#define ARDUINO 165
#define ARDUINO_MAIN
#define F_CPU 16000000L
#define __AVR__
#define F_CPU 16000000L
#define ARDUINO 165
#define ARDUINO_AVR_PRO
#define ARDUINO_ARCH_AVR
extern "C" void __cxa_pure_virtual() {;}

//
//
void getError(void);
void calculatePID(void);
void moveServoTilt(float value);
void servo_tilt_update();
void encodeServoTest(char c);

#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\variants\eightanaloginputs\pins_arduino.h" 
#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\arduino.h"
#include <amv-open360tracker.ino>
#include <compass.cpp>
#include <compass.h>
#include <config.h>
#include <defines.h>
#include <eeprom_functions.cpp>
#include <eeprom_functions.h>
#include <frsky.cpp>
#include <frsky_common.h>
#include <frsky_sport.cpp>
#include <gps.cpp>
#include <hott.cpp>
#include <math.cpp>
#include <math.h>
#include <mavlink.cpp>
#include <mfd.cpp>
#include <rvosd.cpp>
#include <sample.c>
#include <servos.h>
#include <settings.cpp>
#include <settings.h>
#include <telemetry.h>
