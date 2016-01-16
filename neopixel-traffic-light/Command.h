#ifndef _COMANND_H_
#define _COMANND_H_

#include "TrafficLight.h"
#include "Alarm.h"

class Command {
public:
  Command(TrafficLight& light, Alarm& alarm);
  
  void process(); 

  TrafficLight& getTrafficLight() { return light_; }
  Alarm& getAlarm() { return alarm_; }
  
private:
  // Functions for parsing
  void restart();
  void execute();
  void discard(const char c);
  void collect(const char c);
  void end1(const char c);

  // Actions
  void off();
  void normal();
  void warning();
  void error();
  void beep();

  // Configure
  void set();
  void setOffset();
  // sizes
  static constexpr unsigned int cBufferSize = 64;
  static constexpr unsigned int cMaxCommands = 10;

  // types
  typedef void (Command::*FSMPtr)(const char c);
  typedef void (Command::*ActionPtr)();

  // command list and actions (static!)
  struct commandPair {
    char *command;
    ActionPtr action;
  };
  static commandPair commands[cMaxCommands];

  // data members
  char buffer_[cBufferSize + 1];
  unsigned int bufferIndex_;
  char *argPtr_;
  FSMPtr currentAction_;
  TrafficLight& light_;
  Alarm& alarm_;
};

#endif
