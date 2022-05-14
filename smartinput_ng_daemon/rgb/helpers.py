"""
Protocol:
Send numbers to the serial port. Send the rgb bytes in that order, then a control byte. Then start over

By default, the control byte is 0x00.
send a control byte of 0x01 after the very last value (blue of last pixel)

"""

import serial
import colorsys

class Device:
  def __init__(self, baudrate=115200, timeout=0.1, port='/dev/ttyUSB0') -> None:
    self.device = serial.Serial(baudrate=baudrate, timeout=timeout, port=port)

  def send_frame(self, colors):
    for i, color in enumerate(colors):
      self.device.write(bytes(color))
      if i == len(colors) - 1:
        self.device.write(bytes([0x01]))
      else:
        self.device.write(bytes([0x00]))

    self.device.flush()

def hsv_to_big_rgb(h, s, v):
  """converts a hsv color with values from 0 to 1 to a rgb tuple with values from 0-255"""
  return tuple([int(i*255) for i in colorsys.hsv_to_rgb(h, s, v)])