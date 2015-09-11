/**
*
* Calculation from cesco1: https://github.com/Cesco1/ManualRTH/blob/master/Nav.ino
*/

#include "math.h"

float lonScale = 1.0f;

void calcTargetDistanceAndHeading(geoCoordinate_t *tracker, geoCoordinate_t *target) {
  int16_t dLat = tracker->lat - target->lat;
  int16_t dLon = (tracker->lon - target->lon);// * lonScale;
  target->distance = uint16_t(sqrt(sq(dLat) + sq(dLon)) * 1.113195f);
  target->heading = uint16_t(atan2(dLon, dLat) * 572.90f);
}

void setHome(geoCoordinate_t *tracker, geoCoordinate_t *target) {
  //todo check if this is correct
  float rads = (abs(float(target->lat)) / 10000000.0) * 0.0174532925;
  lonScale = cos(rads);
  //Serial.print("lon scale: ");
  //Serial.print(lonScale, 6);

  tracker->lat = target->lat;
  tracker->lon = target->lon;
  tracker->alt = target->alt;
  HOME_SET = true;
}
#ifdef TILT_EASING
float easeTilt(float t, float b, float c, float d) {
  #ifdef EASE_OUT_QRT
  return easeOutQuart(t, b, c, d);
  #endif
  #ifdef EASE_INOUT_QRT
  return easeInOutQuart(t, b, c, d);
  #endif
  #ifdef EASE_OUT_CIRC
   return easeOutCirc(t, b, c, d);
  #endif
}

float easeOutQuart(float t, float b, float c, float d) {
    return -c * ((t=t/d-1)*t*t*t - 1) + b;
  }

float easeInOutQuart(float t, float b, float c, float d) {
  t /= d/2;
  if (t < 1) return c/2*t*t*t*t + b;
  t -= 2;
  return -c/2 * (t*t*t*t - 2) + b;
}
float easeOutCirc(float t, float b, float c, float d) {
  t /= d/2;
  if (t < 1) return -c/2 * (sqrt(1 - t*t) - 1) + b;
  t -= 2;
  return c/2 * (sqrt(1 - t*t) + 1) + b;
}
#endif
