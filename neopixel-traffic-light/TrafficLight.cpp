#include "TrafficLight.h"
#include <Arduino.h>
#include <FastLED.h>

namespace {
  const int redPixels[] = {  0, 1, 2, 3, 4, 5 };
  const int orangePixels[] = { 5, 6, 7, 8, 13, 14, 15, 16 };
  const int greenPixels[] = {  8, 9, 10, 11, 12, 13 };
}

TrafficLight::TrafficLight(const unsigned int pixels, const unsigned int offset)
: pixels_(pixels),
  offset_(offset),
  buffer_{},
  actions_{ &TrafficLight::setOff, &TrafficLight::setGreen, &TrafficLight::setOrangeFade, &TrafficLight::setRedBlink },
  processAction_(nullptr),
  time_(),
  colour_(),
  brightness_(0xff),
  angle_(0)
{
  FastLED.addLeds<NEOPIXEL, cDataPin>(buffer_, pixels_);
}

void
TrafficLight::process()
{
  if (processAction_)
    (this->*processAction_)();
}

void
TrafficLight::set(const Status status)
{
  (this->*actions_[status])();
}

void TrafficLight::setAll(const CRGB& colour)
{
  for (unsigned int i = pixels_; i ;)
    buffer_[--i] = colour;
}

void
TrafficLight::setPixels(const int* pixels, unsigned int count, const CRGB& colour)
{
  setAll(CRGB::Black);
  for ( ;count-- ; )
    buffer_[(*pixels++ + offset_) % pixels_] = colour;;
  FastLED.show();
}

void
TrafficLight::setOff()
{
  setAll(CRGB::Black);
  FastLED.show();
  processAction_ = nullptr;
}

void
TrafficLight::setRed()
{
  setPixels(redPixels, sizeof(redPixels) / sizeof(int), CRGB::Red);
  processAction_ = nullptr;
}

void
TrafficLight::setOrange()
{
  setPixels(orangePixels, sizeof(orangePixels) / sizeof(int), CRGB::Orange);
  processAction_ = nullptr;
}

void
TrafficLight::setGreen()
{
  setPixels(greenPixels, sizeof(greenPixels) / sizeof(int), CRGB::Green);
  processAction_ = nullptr;
}

void
TrafficLight::setRedBlink()
{
  processAction_ = &TrafficLight::processBlink;
  colour_ = CRGB::Red;
  brightness_ = 0;
  time_ = cBlinkTime;
}

void
TrafficLight::setOrangeFade()
{
  processAction_ = &TrafficLight::processFade;
  colour_ = CRGB::Orange;
  angle_ = 0;
  time_ = cFadeFrame;
}

void
TrafficLight::processBlink()
{
  if (time_ > cBlinkTime) {
    time_ = 0;
    brightness_ = ~brightness_;
    CRGB c = colour_;
    c.nscale8(brightness_);
    setAll(c);
    FastLED.show();
  }
}

void
TrafficLight::processFade()
{
  if (time_ > cFadeFrame) {
    time_ = 0;
    brightness_ = sin8(angle_);
    angle_ += cFadePhase;
    CRGB c = colour_;
    c.nscale8_video(brightness_);
    setAll(c);
    FastLED.show();
  }
}

