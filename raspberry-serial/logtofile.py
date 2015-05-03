#
# Log all sensor data to file for later push to dusti.xyz api
#
# requires:
# apt-get install python-serial
# pip install pytz
#
# Python 2 code!!
#

import os.path
import serial
import uuid

from sensor import (
    SensorDSM501A,
    SensorGP2Y10,
    SensorPPD42NS,
    SensorSHT10,
    SensorBMP180,
)

dirname = os.path.dirname(os.path.abspath(__file__))
# different filename on each restart
# because you may have to change the location of the sensor
# before uploading the data
filename = os.path.join(dirname, uuid.uuid4().hex)

import argparse
parser = argparse.ArgumentParser()
parser.add_argument("--device", help="device to read from",
                    default="/dev/ttyACM0")
args = parser.parse_args()

classes = (SensorDSM501A, SensorGP2Y10, SensorPPD42NS,
           SensorSHT10, SensorBMP180)

ser = serial.Serial(args.device)
while True:
    message = ser.readline()
    for cls in classes:
        instance = cls(filename)
        data = instance.parse(message)
        if data:
            instance.log(data)
