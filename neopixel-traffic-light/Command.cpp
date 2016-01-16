#include "Command.h"
#include "TrafficLight.h"
#include <Arduino.h>
#include <cstring>
#include <cstdlib>

namespace {
  const char cStart = ':';
  const char cEnd1 = '\r';
  const char cEnd2 = '\n';
  const char cSeparator = ',';
}

Command::commandPair Command::commands[] = {
  {"off", &Command::off},
  {"normal", &Command::normal},
  {"warning", &Command::warning},
  {"error", &Command::error},
  {"beep", &Command::beep},
  {"set", &Command::set},
  {"offset", &Command::setOffset},
  {nullptr, nullptr},
};

Command::Command(TrafficLight& light, Alarm& alarm)
: buffer_{},
  bufferIndex_(0),
  argPtr_(nullptr),
  currentAction_(&Command::discard),
  light_(light),
  alarm_(alarm)
{
  Serial.begin(9600);
}

void
Command::process()
{
  while (Serial.available()) {
    (this->*currentAction_)(Serial.read());
  }
}

void
Command::restart()
{
  bufferIndex_ = 0;
  currentAction_ = &Command::discard;
}
void
Command::discard(const char c)
{
  if (c == cStart) {
    currentAction_ = &Command::collect;
  }
}

void
Command::collect(const char c)
{
  switch (c) {
    case cStart:
      bufferIndex_ = 0;
      break;
    case cEnd1:
      buffer_[bufferIndex_] = 0;
      currentAction_ = &Command::end1;
      break;
    default:
      if (bufferIndex_ < cBufferSize)
        buffer_[bufferIndex_++] = c;
      else
        restart();
      break;;
  }
}

void
Command::end1(const char c)
{
  if (c == cEnd2) 
    Command::execute();
  restart();
}

void
Command::execute()
{
  argPtr_ = index(buffer_, cSeparator);
  if (argPtr_)
    *argPtr_++ = 0;
  for (Command::commandPair *p = commands; p->command != nullptr; ++p) {
    if (strcmp(p->command, buffer_) == 0) {
      Serial.println("OK");
      (this->*(p->action))();
      return;
    }
  }
  Serial.println("ERR");
}

void
Command::off()
{
  light_.set(TrafficLight::off);
}

void
Command::normal()
{
  light_.set(TrafficLight::normal);
}

void
Command::warning()
{
  light_.set(TrafficLight::warning);
}

void
Command::error()
{
  light_.set(TrafficLight::error);
}

void
Command::beep()
{
  unsigned long count = 3;
  if (argPtr_) 
    count = strtoul(argPtr_, nullptr, 10);
  alarm_.beep(count);
}

void
Command::set()
{
  if (argPtr_) {
    if (strcmp(argPtr_, "normal") == 0) {
      light_.setAction(TrafficLight::normal, &TrafficLight::setBottom);
      light_.setAction(TrafficLight::warning, &TrafficLight::setHorizontal);
      light_.setAction(TrafficLight::error, &TrafficLight::setTop);
    }
    if (strcmp(argPtr_, "blink") == 0) {
      light_.setAction(TrafficLight::normal, &TrafficLight::setAll);
      light_.setAction(TrafficLight::warning, &TrafficLight::setCrossBlink);
      light_.setAction(TrafficLight::error, &TrafficLight::setBlink);
      
    }
  }
}

void
Command::setOffset()
{
  unsigned long offset = 0;
  if (argPtr_) 
    offset = strtoul(argPtr_, nullptr, 10);
  light_.setOffset(offset);
}

