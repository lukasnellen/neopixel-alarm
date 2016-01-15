#include "TrafficLight.h"
#include "Alarm.h"
#include "Command.h"

#define DELAY 1000

TrafficLight gLight;
Alarm gAlarm;
Command gCmd(gLight, gAlarm);

void 
setup() 
{
 gLight.set(TrafficLight::off); 
}

void 
loop() 
{
  gCmd.process();
  gLight.process();
  gAlarm.process();
}
