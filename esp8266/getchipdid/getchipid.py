#!/usr/bin/env python
import serial

ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
ser.write('=node.chipid()\n')
ser.flush()

ser.readline()
print("esp8266-{}".format(ser.readline())),
ser.close()

