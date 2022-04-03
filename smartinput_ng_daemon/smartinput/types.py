import enum
from dataclasses import dataclass

class EventType(enum.Enum):
    press = 'P'
    short_press = 'S'
    long_press = 'L'
    release = 'R'

@dataclass
class Event:
  key: int
  event_type: EventType