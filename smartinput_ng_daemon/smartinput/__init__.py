import serial
import time
from smartinput.helpers import wait_for_event
from smartinput.handle import handle_event
import yaml

def main():
    with open("smartinput.yml", "r") as stream:
        config = yaml.safe_load(stream)

    print(config)

    device = serial.Serial(baudrate=9600, timeout=.1, port="/dev/ttyACM1")
    while True:
        event = wait_for_event(device)
        handle_event(event, config['keys'])
        print(event)