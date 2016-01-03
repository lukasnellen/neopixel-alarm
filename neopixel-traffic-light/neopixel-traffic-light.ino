#include "TrafficLight.h"
#include "Command.h"

#define DELAY 1000

TrafficLight gLight;
Command gCmd(gLight);

void 
setup() 
{
 gLight.set(TrafficLight::off); 
}

void 
loop() 
{
  gCmd.process();
}
