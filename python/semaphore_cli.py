#! /usr//bin/env python
"""
Python command line interface for alarm light

.. codeauthor:: Lukas Nellen

"""

from __future__ import print_function
import serial
import argparse
import os
import sys

class config(object):
    """
    Configurator class

    Parses cmannd line and environment variables
    """
    def __init__(self):
        self.build_parser()
        self.args = self.parser.parse_args()

    def build_parser(self):
        """
        Build the command line argument parser.
        """
        self.parser = argparse.ArgumentParser()
        self.parser.add_argument("-p", "--port",
                                 help="Serial port")
        sp = self.parser.add_subparsers(dest="cmd")
        off_parser = sp.add_parser("off",
                                   help="Turn semaphore off")
        normal_parser = sp.add_parser("normal",
                                      help="Set semaphore to normal (ok)")
        warning_parser = sp.add_parser("warning",
                                       help="Set semaphore to warning")
        error_parser = sp.add_parser("error",
                                     help="Set semaphore to error")
        beep_parser = sp.add_parser("beep",
                                    help="Acoustic warning/error")
        beep_parser.add_argument("count", type=int, default="3", nargs="?",
                                 help="Number of beeps")
        mode_parser = sp.add_parser("mode",
                                    help="Set operating mode")
        mode_parser.add_argument("mode", choices=("normal", "blink"),
                                 help="Operating mode")
        offset_parser = sp.add_parser("offset",
                                      help="Set pixel offset")
        offset_parser.add_argument("count", type=int, default="0", nargs="?",
                                   help="Offset for first pixel")
        scale_parser = sp.add_parser("scale",
                                      help="Set brightness scale")
        scale_parser.add_argument("count", type=int, default="255", nargs="?",
                                   help="Scale for brightness (0-255)")

    @property
    def port(self):
        """
        Serial port to use

        :return: string
        """
        if self.args.port is not None:
            return self.args.port
        try:
            return os.environ["SEMAPHORE_PORT"]
        except KeyError:
            print("Error: Serial port not specified, use \"-p\" or set ${SEMAPHORE_PORT}", file=sys.stderr)
            sys.exit(1)

class main(object):
    """
    Main routine class

    Provides member functions for all sub-commands.
    """
    def __init__(self):
        self.cfg=config()

    def run(self):
        """
        Main entry point for the script. Gets called when running the module.
        """
        self.ser = serial.Serial(self.cfg.port)

        # empty message to reset communications
        self.ser.write(":\r\n")

        cmd = self.cfg.args.cmd
        self.commands[cmd](self)

    def off(self):
        self.ser.write(":off\r\n")

    def normal(self):
        self.ser.write(":normal\r\n")

    def warning(self):
        self.ser.write(":warning\r\n")

    def error(self):
        self.ser.write(":error\r\n")

    def beep(self):
        self.ser.write(":beep,{}\r\n".format(self.cfg.args.count))

    def mode(self):
        self.ser.write(":set,{}\r\n".format(self.cfg.args.mode))

    def offset(self):
        self.ser.write(":offset,{}\r\n".format(self.cfg.args.count))

    def scale(self):
        self.ser.write(":scale,{}\r\n".format(self.cfg.args.count))

    commands = dict(off=off, normal=normal, warning=warning, error=error,
                    beep=beep, mode=mode, offset=offset, scale=scale)

if __name__ == "__main__":
    main().run()
