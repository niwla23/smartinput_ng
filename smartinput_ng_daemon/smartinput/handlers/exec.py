from smartinput.handlers.base import BaseHandler
from smartinput.types import Event
import os

class ExecHandler(BaseHandler):
  def __init__(self) -> None:
    self.params = {}

  def handle_event(self, event: Event):
    os.system(self.params['command'])

  def set_params(self, params: dict):
    self.params = params
