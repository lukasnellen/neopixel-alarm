Simple Neopixel Alarm light
===========================

The alarm light consists of a [16 pixel NeoPixel ring][1], controlled by a
[Teensy LC][2] micro-controller. Additionally, a piezo buzzer can emit beeps.

The device can be controlled by sending commands over the serial port
(emulated via USB).

A simple command-line interface `semaphore_cli.py` provides a
[command line tool][3] to send commands over USB to the device.

[1]: https://www.adafruit.com/products/1463 "Adafruit 16 pixel NeoPixel ring"
[2]: https://www.pjrc.com/teensy/teensyLC.html "Teensy LC micro-controller"
[3]: cli.md "Command line interface documentation"
