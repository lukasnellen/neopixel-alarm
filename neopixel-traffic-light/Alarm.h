#ifndef _ALARM_H_
#define _ALARM_H_

#include "Hardware.h"
#include <elapsedMillis.h>

class Alarm {
public:

  Alarm(const unsigned int frequency = Hardware::buzzerFrequency) : frequency_(frequency) { };

  void process();

  void beep(const unsigned int count = 1);

private:

  void beepOnce();

  unsigned int frequency_;
  unsigned int count_;
  elapsedMillis time_;

};
#endif

