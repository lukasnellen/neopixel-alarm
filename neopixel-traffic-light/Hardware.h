#ifndef _HARDWARE_H_
#define _HARDWARE_H_
/**
 * \file
 * \brief Collection of hardware information
 * 
 * Describe the hardware in one file, e.g., pin numbers, array sizes, ...
 */


namespace Hardware {
  // Pixel strip
  constexpr unsigned int ledPin = 17;            ///< Pin 17 has 5v driver on Teensy LC
  constexpr unsigned int leds = 16;              ///< NUmber of pixels: 16 for Neopixel ring

  // Blinking and fading
  constexpr unsigned int blinkTime = 1000;      ///< Time for on and off when blinking [ms]
  constexpr unsigned int fadeFrame = 40;        ///< Frame duration for fading [ms]: 25 / ss
  constexpr unsigned int fadePhase = 4;         ///< phase to step brightness per frame (angle 0..255)

  // Serial interface related
  constexpr unsigned int serialUSBLed = 13;        ///< Teensy 3.x, LC internal led pin

  // Buzzer
  constexpr unsigned int buzzerPin = 6;          ///< Pin where buzzer connected
  constexpr unsigned int buzzerFrequency = 4000; ///< buzzer frequence [Hz]
  constexpr unsigned int beepDuration = 500;     ///< Duration of beep [ms]
  constexpr unsigned int beepInterval = 1000;    ///< Total interval (silence and beep) for repeated beeps [ms]
  
};
#endif

