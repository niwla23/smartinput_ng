"""
Protocol:
Send numbers to the serial port. Send the rgb bytes in that order, then a control byte. Then start over

By default, the control byte is 0x00.
send a control byte of 0x01 after the very last value (blue of last pixel)

"""

import serial
import time
import colorsys

device = serial.Serial(baudrate=9600, timeout=.1, port='/dev/ttyUSB0')


def send_frame(colors):
  for i, color in enumerate(colors):
    device.write(bytes(color))
    if i == len(colors) - 1:
      device.write(bytes([0x01]))
    else:
      device.write(bytes([0x00]))

  device.flush()

for i in range(255):
  rgb_color = [int(i*255) for i in colorsys.hsv_to_rgb(i / 255, 1, 1)]

  send_frame([rgb_color]*4)
  time.sleep(0.01)