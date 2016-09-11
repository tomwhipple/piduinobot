Arduino/Pi robot
================

A robot built from Make Arduino robot kit. Arduino is an Wyolum AlaMode board sitting on top of a RaspberryPi. The Pi has a USB WiFi adapter, so we can SSH to the robot for quicker debugging & control.

Software prerequisates
----------------------

We'd prefer not to run any UI on the Pi, and instead connect from a computer. So we need:

- Samba & avahi, for easy "local" file editing. (OSX is moving to SMB2)
    `# apt-get install samba samba-common-bin avahi-daemon avahi-utils`
- avr tools
- ino (command line Arduino builds)

Quickstart
----------

Use `ino` command.

- Compile with `ino build`.
- Upload (from pi) with `ino upload`.
- Connect with `ino serial`. (note upload also uses serial, the two cannot be run simultaneously

