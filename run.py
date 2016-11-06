#!/usr/bin/env python

import os
import sys

from datetime import datetime

import serial
import json

import KBHit

SERIAL_PORT = '/dev/ttyS0'
SERIAL_BAUD = 9600

script_dir = os.path.dirname(os.path.realpath(__file__))
start_time = datetime.now()
log_dir = os.path.join(script_dir, 'log')

if not os.path.exists(log_dir):
  os.makedirs(log_dir)

#log_file = start_time.strftime("event-%y%m%d-%H%M%S.log")
log_file = start_time.strftime("event-%Y%m%d.log")
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
    print "+: increase velocity"
    print "-: decrease velocity"
    print ">: rotate right"
    print "<: rotate left"
    print "=: stop rotation"
    print "r: head right"
    print "l: head left"
    print "<space>: all stop"
    print "<esc>: exit & all stop"

    # first line will be garbage
    ser.readline() 

    while running:
      if kb.kbhit():
        key = kb.getch()
        if ord(key) == 27: #ESC
          running = False
          key = ' '

        ser.write(key)
        log_event({'command_sent': key})
        
      try: 
        line = ser.readline()
        event = json.loads(line[:-3])
        log_event(event)

      except ValueError as ve:
        print "Communication error: {0}".format(ve)
        #import pdb; pdb.set_trace()
