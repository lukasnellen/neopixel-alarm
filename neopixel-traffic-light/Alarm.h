#ifndef _ALARM_H_
#define _ALARM_H_
/**
 * \file
 * \brief Definitions for audible alarm control
 * 
 * \author Lukas Nellen
 */

#include "Hardware.h"
#include <elapsedMillis.h>

/**
   \brief Audible alarm controller
   Class to handle buzzer for audible alarm

   \author Lukas Nellen
 */
class Alarm {
public:

  /// Constructor, sets frequency
  Alarm(const unsigned int frequency = Hardware::buzzerFrequency) : frequency_(frequency) { };

  /// Processing in main loop
  void process();

  /// Start beeping. Returns immediatly, beeping happens in background
  void beep(const unsigned int count = 1);

private:

  void beepOnce();

  unsigned int frequency_; ///< Beep frequency
  unsigned int count_;     ///< Number of beeps pending
  elapsedMillis time_;     ///< time delta for groups of beeps

};
#endif

