from helpers import Device, hsv_to_big_rgb
import constants
import colors
import time

device = Device(constants.baudrate, constants.timeout, constants.port)

while True:
    shift = 0
    while shift < 1:
        framebuffer = []
        for pixel in range(constants.num_pixels):
            framebuffer.append(hsv_to_big_rgb(
                pixel/constants.num_pixels + shift, 1, 1))
        device.send_frame(framebuffer)
        time.sleep(0.01)
        shift += 0.001
