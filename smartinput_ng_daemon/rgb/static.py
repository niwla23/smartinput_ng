from helpers import Device
import constants
import colors

device = Device(constants.baudrate, constants.timeout, constants.port)
device.send_frame([colors.BLUE]*4)
