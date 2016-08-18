#include "TrafficLight.h"
#include <Arduino.h>
#include <FastLED.h>

namespace {
  const int topPixels[] = {  0, 1, 2, 15, 14, 13 };
  const int horizontalPixels[] = { 2, 3, 4, 5, 10, 11, 12, 13};
  const int bottomPixels[] = {  5, 6, 7, 8, 9, 10 };
  const int verticalPixels[] = { 0, 1, 14, 15, 6, 7, 8, 9 };
}

TrafficLight::TrafficLight(const unsigned int offset)
: offset_(offset),
  buffer_{},
  actions_{ &TrafficLight::setAll, &TrafficLight::setBottom, &TrafficLight::setHorizontal, &TrafficLight::setTop },
  actionColour_{ CRGB::Black, CRGB::Green, CRGB::Orange, CRGB::Red },
  processAction_(nullptr),
  time_(),
  colour_(),
  brightness_(0xff),
  scale_(0x7f),
  angle_(0),
  pos_(0)
{
  FastLED.addLeds<NEOPIXEL, Hardware::ledPin>(buffer_, Hardware::leds);
}

/**
 * Processing loop action. This is used to implement dynamical actions like
 * blinking or fading of pixels. The selected action is set using the
 * internal processAction_ pointer.
 */
void
TrafficLight::process()
{
  if (processAction_)
    (this->*processAction_)();
}

void
TrafficLight::set(const Status status)
{
  (this->*actions_[status])(actionColour_[status]);
}

void
TrafficLight::setAction(const Status status, ActionPtr action)
{
  actions_[status] = action;
}

void
TrafficLight::setPixels(const int* pixels, unsigned int count, const CRGB& colour)
{
  FastLED.clear(true);
  for ( ;count-- ; )
    buffer_[(*pixels++ + offset_) % Hardware::leds] = colour;;
  FastLED.show(scale_);
}

void TrafficLight::setAll(const CRGB& colour)
{
  FastLED.showColor(colour, scale_);
  processAction_ = nullptr;
}

void
TrafficLight::setTop(const CRGB& colour)
{
  setPixels(topPixels, sizeof(topPixels) / sizeof(int), colour);
  processAction_ = nullptr;
}

void
TrafficLight::setBottom(const CRGB& colour)
{
  setPixels(bottomPixels, sizeof(bottomPixels) / sizeof(int), colour);
  processAction_ = nullptr;
}

void
TrafficLight::setHorizontal(const CRGB& colour)
{
  setPixels(horizontalPixels, sizeof(horizontalPixels) / sizeof(int), colour);
  processAction_ = nullptr;
}

void
TrafficLight::setVertical(const CRGB& colour)
{
  setPixels(verticalPixels, sizeof(verticalPixels) / sizeof(int), colour);
  processAction_ = nullptr;
}

void
TrafficLight::setBlink(const CRGB& colour)
{
  processAction_ = &TrafficLight::processBlink;
  colour_ = colour;
  brightness_ = 0;
  time_ = Hardware::blinkTime;
}

void
TrafficLight::setFade(const CRGB& colour)
{
  processAction_ = &TrafficLight::processFade;
  colour_ = colour;
  angle_ = 0;
  time_ = Hardware::fadeFrame;
}

void
TrafficLight::setCrossBlink(const CRGB& colour)
{
  processAction_ = &TrafficLight::processCrossBlink;
  pos_ = 0;
  colour_ = colour;
  time_ = Hardware::blinkTime;
}

void
TrafficLight::processBlink()
{
  if (time_ > Hardware::blinkTime) {
    time_ = 0;
    brightness_ = ~brightness_;
    FastLED.showColor(colour_, scale8(brightness_, scale_));
  }
}

void
TrafficLight::processFade()
{
  if (time_ > Hardware::fadeFrame) {
    time_ = 0;
    brightness_ = sin8(angle_);
    angle_ += Hardware::fadePhase;
    FastLED.showColor(colour_, scale8(brightness_, scale_));
  }
}

void
TrafficLight::processCrossBlink()
{
  if (time_ > Hardware::blinkTime) {
    time_ = 0;
    pos_ ^= 1;
    if (pos_)
      setPixels(horizontalPixels, sizeof(horizontalPixels) / sizeof(int), colour_);
    else
      setPixels(verticalPixels, sizeof(verticalPixels) / sizeof(int), colour_);
  }
}

