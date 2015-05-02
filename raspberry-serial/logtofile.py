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
)

dirname = os.path.dirname(os.path.abspath(__file__))
# different filename on each restart
# because you may have to change the location of the sensor
# before uploading the data
filename = os.path.join(dirname, uuid.uuid4().hex)

# FIXME: parameterize ttyACM0 or ttyACM1

import argparse
parser = argparse.ArgumentParser()
parser.add_argument("--device", help="device to read from",
                    default="/dev/ttyACM0")
args = parser.parse_args()

ser = serial.Serial(args.device)
while True:
    message = ser.readline()
    ppd = SensorPPD42NS(filename)
    data = ppd.parse(message)
    if data:
        ppd.log(data)

    sht10 = SensorSHT10(filename)
    data = sht10.parse(message)
    if data:
        sht10.log(data)

    gp2y10 = SensorGP2Y10(filename)
    data = gp2y10.parse(message)
    if data:
        gp2y10.log(data)

    dsm501a = SensorDSM501A(filename)
    data = dsm501a.parse(message)
    if data:
        dsm501a.log(data)
