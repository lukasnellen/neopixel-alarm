#include "Command.h"
#include "TrafficLight.h"
#include <Arduino.h>
#include <cstring>

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
  {nullptr, nullptr},
};

Command::Command(TrafficLight& light)
: buffer_{},
  bufferIndex_(0),
  argPtr_(nullptr),
  currentAction_(&Command::discard),
  light_(light)
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

