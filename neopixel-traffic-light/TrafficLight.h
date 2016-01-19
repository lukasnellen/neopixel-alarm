#ifndef _TRAFFICLIGHT_H_
#define _TRAFFICLIGHT_H_
/**
 * \file
 * \brief Traffic-light controller
 *
 * \author Lukas Nellen
 */

#include "Hardware.h"
#include <FastLED.h>
#include <elapsedMillis.h>
#include <cstdint>

/**
 * \brief NeoPixel Traffic Light controller
 *
 * Controller to display different status conditions using a NeoPixel ring.
 *
 * The code is set up for a Teensy LC microcontroller and a 16 pixel NeoPixel
 * ring.
 *
 * A pixel offset can be set to handle the device being installed in vertical or
 * horizontal orientation.
 */
class TrafficLight
{
public:
  /// Status conditions that can be displayed
  enum Status {
    off,       ///< light off
    normal,    ///< normal condition
    warning,   ///< warning condition
    error,     ///< error condition
    maxStatus  ///< Maximal status (+1), to dimension arrays
  };

  /// Function type for actions to be executed when setting status
  typedef void (TrafficLight::*ActionPtr)(const CRGB& );
  /// Action to be executed in process loop.
  typedef void (TrafficLight::*ProcessPtr)();

  /// Constructor, with pixel offset
  TrafficLight(const unsigned int offset = 0);

  /// Action function, to be called in main processing loop
  void process();

  /// Set status using Status enumerator
  void set(const Status status);
  /// Set the action to be associated with a given Status
  void setAction(const Status status, ActionPtr action);
  /// Set the offset
  void setOffset(const unsigned int offset = 0) { offset_ = offset % Hardware::leds; }

  /** \name Physical actions
    */
  ///@{
  /// \brief Light the top pixels in \a colour.
  void setTop(const CRGB& colour);
  /// Light the bototm pixels in \a colour.
  void setBottom(const CRGB& colour);
  /// Light a horizontal group of pixels in \a colour.
  void setHorizontal(const CRGB& colour);
  /// Light a vertical group of pixels in \a colour.
  void setVertical(const CRGB& colour);
  /// Light all pixels in \a colour.
  void setAll(const CRGB& colour);
  /// Blink all pixels in \a colour
  void setBlink(const CRGB& colour);
  /// Blink alternating horizontal and vertical pixels in \a colour.
  void setCrossBlink(const CRGB& colour);
  /// Fade all pixels on and off in \a colour
  void setFade(const CRGB& colour);
  ///@}
//  void set(const CRGB& colour);

private:

  void setPixels(const int*, unsigned int count, const CRGB& colour);

  void processBlink();
  void processFade();
  void processCrossBlink();

  unsigned int offset_;

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

