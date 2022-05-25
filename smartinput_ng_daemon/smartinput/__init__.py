import serial
from serial.tools.list_ports import comports
import time
from smartinput.helpers import wait_for_event
from smartinput.handle import handle_event
from smartinput.rgb.effects.rainbow import rainbow
from smartinput.rgb import constants
from smartinput.rgb.helpers import RGBDevice
from smartinput.server import run_in_thread
import yaml                     


def main(config_path: str):
    with open(config_path, "r") as stream:
        config = yaml.safe_load(stream)

    hwid = config['device']

    port = None
    for device in comports():
        if device.hwid == hwid:
            port = device.device
    print(port)
    if not port:
        raise Exception(f"device with hwid {hwid} not found.")

    device = serial.Serial(baudrate=config['baudrate'], timeout=.1, port=port)


    run_in_thread(device)

    while True:
        event = wait_for_event(device)
        print(event)
        handle_event(event, config['keys'])