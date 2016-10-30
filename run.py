#!/usr/bin/env python

import os
import sys

from datetime import datetime

import serial
import json

SERIAL_PORT = '/dev/ttyS0'
SERIAL_BAUD = 9600

script_dir = os.path.dirname(os.path.realpath(__file__))
start_time = datetime.now()
log_dir = os.path.join(script_dir, 'log')

if not os.path.exists(log_dir):
  os.makedirs(log_dir)

log_file = start_time.strftime("event-%y%m%d-%H%M%S.log")
log_path = os.path.join(log_dir, log_file)

with open(log_path, 'a') as log_file:
  with serial.Serial(SERIAL_PORT, SERIAL_BAUD) as ser:

    # first line will be garbage
    ser.readline()

    while True:
      try: 
        line = ser.readline()
  
        event = json.loads(line[:-3])
        event['at'] = datetime.now().isoformat()
  
        log_file.write(json.dumps(event, sort_keys=True))
        log_file.write("\n")
        log_file.flush()
      except ValueError as ve:
        print "Communication error: {0}".format(ve)
        import pdb; pdb.set_trace()
