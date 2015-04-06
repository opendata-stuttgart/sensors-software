#
# Push data live to API using Python on a RaspberryPi
#

import serial
from utils import parse_data, send_data

ser = serial.Serial('/dev/ttyACM0')
while True:
    message = ser.readline()
    data = parse_data(message)
    if data:
        send_data(data)
