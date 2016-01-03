#ifndef _TRAFFICLIGHT_H_
#define _TRAFFICLIGHT_H_
// Traffic light class
// Author: Lukas Nellen

#include <FastLED.h>

// defaults for use with Teesy LC
// 16 pixel NeoPixel ring


class TrafficLight
{
public:
  enum Status {
    off, normal, warning, error, maxStatus
  };
  
  TrafficLight(const unsigned int pixels = 16, const unsigned int offset = 13);

  // update pixels, to be called in main loop or special thread
  //void process();

  // set logical status
  void set(const Status status);

  // set physical status
  void setOff(const bool show);
  void setOff() { setOff(true); };

  void setRed();

  void setOrange();

  void setGreen();

  //void setRedAll(const bool move = true);

  //void setOrangeAll(const bool move = true);

  //void setGreenAll(const bool move = false);
  
private:
  static const unsigned int cMaxPixels = 64;
  static const unsigned char cDataPin = 17;         // Teensy LC pin with 5V level shifter

  void setPixels(const int*, unsigned int count, const CRGB& colour);
  
  const unsigned int pixels_;
  const unsigned int offset_;

  CRGB buffer_[cMaxPixels];

  typedef void (TrafficLight::*ActionPtr)();

  ActionPtr actions_[maxStatus];
};

#endif

