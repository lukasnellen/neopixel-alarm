#ifndef _TRAFFICLIGHT_H_
#define _TRAFFICLIGHT_H_
// Traffic light class
// Author: Lukas Nellen

#include <FastLED.h>
#include <cstdint>

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
  void process();

  // set logical status
  void set(const Status status);

  // set physical status
  void setOff();

  void setRed();

  void setOrange();

  void setGreen();

  void setOrangeFade();
  
  void setRedBlink();
    
private:
  static constexpr unsigned int cMaxPixels = 64;
  static constexpr unsigned char cDataPin = 17;         // Teensy LC pin with 5V level shifter
  static constexpr unsigned int cBlinkTime = 1000;      // Time for on and off when blinking
  static constexpr unsigned int cFadeFrame = 40;        // 25 frames per second
  static constexpr unsigned int cFadePhase = 4;         // phase to step brightness per frame (angle 0..255)
  

  void setAll(const CRGB& colour);

  void setPixels(const int*, unsigned int count, const CRGB& colour);

  void processBlink();
  void processFade();
  
  const unsigned int pixels_;
  const unsigned int offset_;

  CRGB buffer_[cMaxPixels];

  typedef void (TrafficLight::*ActionPtr)();

  ActionPtr actions_[maxStatus];

  ActionPtr processAction_;

  // for blinking or fading
  CEveryNMillis timer_;
  CRGB colour_;
  uint8_t brightness_; 
  uint8_t angle_;
};

#endif

