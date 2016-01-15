#ifndef _HARDWARE_H_
#define _HARDWARE_H_

//
// Hardware information collected in one file
//

namespace Hardware {
  // Pixel strip
  constexpr unsigned int ledPin = 17;            // Teensy LC pin with 5V driver
  constexpr unsigned int leds = 16;              // Neopixel ring

  // Blinking and fading
  constexpr unsigned int blinkTime = 1000;      // Time for on and off when blinking
  constexpr unsigned int fadeFrame = 40;        // 25 frames per second
  constexpr unsigned int fadePhase = 4;         // phase to step brightness per frame (angle 0..255)

  // Buzzer
  constexpr unsigned int buzzerPin = 3;
  constexpr unsigned int buzzerFrequency = 4000; // 4kHz buzzer
  constexpr unsigned int beepDuration = 500;     // in ms
  constexpr unsigned int beepInterval = 1000;    // in ms; intervall for multiple beeps
  
};
#endif

