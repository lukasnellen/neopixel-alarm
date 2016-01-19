Command line interface
======================
A simple python script to send commands to the alarm light.

Usage
-----

The package provides the shell command :command:`semaphore_cli.py`. It handles several sub-commands with options.

<dl>
  <dt>off</dt>
  <dd>Turn leds off</dd>

  <dt>normal</dt>
  <dd>Indicate normal operations, typically by setting the bottom set of pixels to green.<dd>

  <dt>warning</dt>
  <dd>Indicate a warning is present, typically by setting the middle group of pixels to orange.</dd>

  <dt>error</dt>
  <dd>Indicate an error is present, typically by setting the top group of pixels to red.</dd>

  <dt>beep [count]</dt>
  <dd>Beep *count* times. (Default: 3)</dd>

  <dt>mode {normal,blink}</dt>
  <dd>Select the mode to determine what to display for sub-commands like `warning` or `error`.

   *normal*
     Use pixel groups and colour to indicate status.

   *blink*
     Use blinking and colour to indicate status.
   </dd>

  <dt>offset *count*</dt>
  <dd>Rotate the pixel output by *count* positions. This can be used if the device is rotated, e.g.
  by putting it on its side.</dd>
</dl>


### Example

To turn the light off, type:

    semaphore_cli.py off

And to get 5 beeps, type:

    semaphore_cli.py beep 5
