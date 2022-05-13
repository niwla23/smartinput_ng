from smartinput import main
import logging
import os

if __name__ == "__main__":
    logging.basicConfig()
    logging.getLogger().setLevel(logging.INFO)

    config_path = os.environ.get(
        "SMARTINPUT_CONFIG_PATH") or "/etc/smartinput/smartinput.yml"

    main(config_path)
