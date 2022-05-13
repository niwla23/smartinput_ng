import serial
from serial.tools.list_ports import comports
import time
from smartinput.helpers import wait_for_event
from smartinput.handle import handle_event
import yaml

def main(config_path: str):
    with open(config_path, "r") as stream:
        config = yaml.safe_load(stream)

    serial_number = config['device']

    port = None
    for device in comports():
        if device.serial_number == serial_number:
            port = device.device
    
    if not port:
        raise Exception(f"device for serial number {serial_number} not found.")

    device = serial.Serial(baudrate=config['baudrate'], timeout=.1, port=port)
    while True:
        event = wait_for_event(device)
        handle_event(event, config['keys'])