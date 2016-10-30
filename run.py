#!/usr/bin/env python

import os
import sys

from datetime import datetime

import serial
import json

import KBHit

SERIAL_PORT = '/dev/ttyS0'
SERIAL_BAUD = 9600

COMMANDS = {
    'f': 'fwd',
    'r': 'rev',
    ',': 'right',
    '.': 'left',
    ' ': 'stop',
    }


script_dir = os.path.dirname(os.path.realpath(__file__))
start_time = datetime.now()
log_dir = os.path.join(script_dir, 'log')

if not os.path.exists(log_dir):
  os.makedirs(log_dir)

log_file = start_time.strftime("event-%y%m%d-%H%M%S.log")
log_path = os.path.join(log_dir, log_file)

def log_event(event):
  event['at'] = datetime.now().isoformat()
  
  log_file.write(json.dumps(event, sort_keys=True))
  log_file.write("\n")
  log_file.flush()
  
with open(log_path, 'a') as log_file:
  with serial.Serial(SERIAL_PORT, SERIAL_BAUD) as ser:
    running = True
    kb = KBHit.KBHit()

    print "Commands:"
    print "Rotate: left/right arrows"
    print "Move: forward/back arrows"
    print "Stop: space"
    print "Exit: ESC (will stop motion)"

    # first line will be garbage
    ser.readline() 

    while running:
      command = None

      if kb.kbhit():
        key = kb.getch()
        if ord(key) == 27: #ESC
          running = False
          command = 'stop'
        else:
          command = COMMANDS.get(key)

        if command is None:
          print "Uknown key: {0}".format(key)

      try: 
        line = ser.readline()
        event = json.loads(line[:-3])
        log_event(event)

        if command is not None:
          ser.write("{0}\n".format(command))
          log_event({'command_sent': command})
        
      except ValueError as ve:
        print "Communication error: {0}".format(ve)
        #import pdb; pdb.set_trace()
