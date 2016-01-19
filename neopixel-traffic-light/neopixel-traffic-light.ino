#include "TrafficLight.h"
#include "Alarm.h"
#include "Command.h"

TrafficLight gLight;
Alarm gAlarm;
Command gCmd(gLight, gAlarm);

void 
setup() 
{

}

void 
loop() 
{
  gCmd.process();
  gLight.process();
  gAlarm.process();
}
