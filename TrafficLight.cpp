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
  actions_{ &TrafficLight::setOff, &TrafficLight::setGreen, &TrafficLight::setOrange, &TrafficLight::setRed }
{
  FastLED.addLeds<NEOPIXEL, cDataPin>(buffer_, pixels_);
}

void
TrafficLight::set(const Status status)
{
  (this->*actions_[status])();
}

void TrafficLight::setOff(const bool show)
{
  for (unsigned int i = pixels_; i ;)
    buffer_[--i] = CRGB::Black;
  if (show)
    FastLED.show();
}

void
TrafficLight::setPixels(const int* pixels, unsigned int count, const CRGB& colour)
{
  setOff(false);
  for ( ;count-- ; )
    buffer_[(*pixels++ + offset_) % pixels_] = colour;;
  FastLED.show();
}

void
TrafficLight::setRed()
{
  setPixels(redPixels, sizeof(redPixels) / sizeof(int), CRGB::Red);
}

void
TrafficLight::setOrange()
{
  setPixels(orangePixels, sizeof(orangePixels) / sizeof(int), CRGB::Orange);
}

void
TrafficLight::setGreen()
{
  setPixels(greenPixels, sizeof(greenPixels) / sizeof(int), CRGB::Green);
}

