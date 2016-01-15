#include "Alarm.h"
#include "Hardware.h"
#include <Arduino.h>

void
Alarm::process()
{
  if (count_ && time_ > Hardware::beepInterval) {
    time_ = 0;
    --count_;
    beepOnce();
  }
}

void
Alarm::beepOnce()
{
  tone(Hardware::buzzerPin, frequency_, Hardware::beepDuration);
}

void 
Alarm::beep(const unsigned int count)
{
  count_ = count;
  time_ = Hardware::beepInterval;
}

