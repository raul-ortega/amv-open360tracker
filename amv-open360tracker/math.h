#ifndef MATH_H
#define MATH_H

#include "inttypes.h"
#include "defines.h"
#include "Arduino.h"

void calcTargetDistanceAndHeading(geoCoordinate_t *tracker, geoCoordinate_t *target);
void setHome(geoCoordinate_t *tracker, geoCoordinate_t *target);
//Easing functions
#define TILT_EASING
  float easeTilt(float t, float b, float c, float d);
  float easeOutQuart(float t, float b, float c, float d);
  float easeInOutQuart(float t, float b, float c, float d);
  float easeOutCirc(float t, float b, float c, float d);
#endif
