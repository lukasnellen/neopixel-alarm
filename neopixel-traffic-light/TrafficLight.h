#ifndef _TRAFFICLIGHT_H_
#define _TRAFFICLIGHT_H_
// Traffic light class
// Author: Lukas Nellen

#include "Hardware.h"
#include <FastLED.h>
#include <elapsedMillis.h>
#include <cstdint>

// defaults for use with Teesy LC
// 16 pixel NeoPixel ring


class TrafficLight
{

public:
  enum Status {
    off, normal, warning, error, maxStatus
  };
  
  typedef void (TrafficLight::*ActionPtr)(const CRGB& );
  typedef void (TrafficLight::*ProcessPtr)();

  TrafficLight(const unsigned int offset = 0);

  // update pixels, to be called in main loop or special thread
  void process();

  // set logical status
  void set(const Status status);
  void setAction(const Status status, ActionPtr action);

  // set physical status
  void setTop(const CRGB& colour);
  void setBottom(const CRGB& colour);
  void setHorizontal(const CRGB& colour);
  void setVertical(const CRGB& colour);
  void setAll(const CRGB& colour);
  void setBlink(const CRGB& colour);
  void setCrossBlink(const CRGB& colour);
  void setFade(const CRGB& colour);
//  void set(const CRGB& colour);
    
private:
  
  void setPixels(const int*, unsigned int count, const CRGB& colour);

  void processBlink();
  void processFade();
  void processCrossBlink();
  
  const unsigned int offset_;

  CRGB buffer_[Hardware::leds];

  ActionPtr actions_[maxStatus];
  CRGB actionColour_[maxStatus];

  ProcessPtr processAction_;

  // for blinking or fading
  elapsedMillis time_;
  CRGB colour_;
  uint8_t brightness_; 
  uint8_t angle_;
  long int pos_;
};

#endif

