/**
 * \file
 * \brief Main sketch
 */
#include "TrafficLight.h"
#include "Alarm.h"
#include "Command.h"

TrafficLight gLight;
Alarm gAlarm;
Command gCmd(gLight, gAlarm);

/// Standard Arduino setup functions
/**
 * We do the real setup in the constructors of the global objects,
 * so nothing to do here
 */
void
setup()
{

}

/// Main loop
/**
 * Calls the process function in all active classes.
 * Continuous looping implements a polling mechanism.
 */
void
loop()
{
  gCmd.process();
  gLight.process();
  gAlarm.process();
}
