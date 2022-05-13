"""
Protocol:
Send numbers to the serial port. First send red byte, then green byte, then blue byte.
\n Switches to the next pixel
\r Actually applies the colors and switches to pixel 0

"""

import serial

device = serial.Serial(baudrate=9600, timeout=.1, port='/dev/ttyUSB0')

colors = [(255, 0, 0), (0, 255, 0), (0, 0, 255)]

for color in colors:
  device.write(bytes(color))
  device.write(b'\n')

device.write(b'\r')