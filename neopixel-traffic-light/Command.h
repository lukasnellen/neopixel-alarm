#ifndef _COMANND_H_
#define _COMANND_H_
/**
 * \file
 * \brief Comand parser and interpreter
 *
 * \author Lukas Nellen
 */
#include "TrafficLight.h"
#include "Alarm.h"

/**
 * \brief Comand parser and interpreter
 *
 * Handle messages via serial port
 * - parse
 * - execute
 *
 * The format of the messages is:
 * >  :cmd\<CR>\<LF>
 * or
 * >  :cmd,arg\<CR>\<LF>
 * The parser will reply with
 * > OK\<CR>\<LF>
 * if `cmd` is a valid command and
 * > ERR\<CR>\<LF>
 * if `cmd` is not recognized. The interpretation of
 * `arg` is left to the command's subroutine.
 *
 * The **parser** is implemented as a FSM.
 * Each state has a function associated, which handles the
 * current input and decides on the next state
 * The state is recorded by setting a pointer to the currenty
 * active state function.
 *
 * The command interpreter dispatches to a command action
 * function. This function will often manipulated the owned
 * action objects (TrafficLight and Alarm).
 *
 * \author Lukas Nellen
 */
class Command {
public:
  /// Constructor, connects to action objects
  Command(TrafficLight& light, Alarm& alarm);

  /// Action for main processing loop
  void process();

  /// Get light controller
  TrafficLight& getTrafficLight() { return light_; }
  /// Get buzzer controller
  Alarm& getAlarm() { return alarm_; }

private:
  // State functions for parsing
  void restart();
  void execute();
  void discard(const char c);
  void collect(const char c);
  void end1(const char c);

  // Command actions
  void off();
  void normal();
  void warning();
  void error();
  void beep();

  // Configure commands
  void set();
  void setOffset();
  void setScale();

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
  bool usbConnected_;
};

#endif
