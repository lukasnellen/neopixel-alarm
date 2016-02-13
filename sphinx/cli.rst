Command line interface
======================

A simple python script to send commands to the alarm light.

Usage
-----

The package provides the shell command :command:`semaphore_cli.py`. It handles several sub-commands with options.

.. option:: off

   Turn leds off

.. option:: normal

   Indicate normal operations, typically by setting the bottom set of pixels to green.

.. option:: warning

   Indicate a warning is present, typically by setting the middle group of pixels to orange.

.. option:: error

   Indicate an error is present, typically by setting the top group of pixels to red.

.. option:: beep [count]

   Beep *count* times. (Default: 3)

.. option:: mode {normal,blink}

   Select the mode to determine what to display for options like :option:`warning` or :option:`error`.

   normal
     Use pixel groups and colour to indicate satus.

   blink
     Use blinking and colour to indicate status.

.. option:: offset count

   Rotate the pixle output by *count* positions. This can be used if the device is rotated, e.g.
   by putting it on its side.

Example
^^^^^^^

.. highlight:: sh

To turn the light off, type::

   semaphore_cli.py off

And to get 5 beeps, type::

  semaphore_cli.py beep 5


Code
----

.. automodule:: semaphore_cli
   :members:
