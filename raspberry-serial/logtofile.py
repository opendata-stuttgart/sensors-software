#
# Log all sensor data to file for later push to dusti.xyz api
#
# requires:
# apt-get install python-serial
# pip install pytz
#
# Python 2 code!!
#

from datetime import datetime
import json
import os.path
import pytz
import serial
import uuid

from utils import parse_data


dirname = os.path.dirname(os.path.abspath(__file__))
# different filename on each restart
# because you may have to change the location of the sensor
# before uploading the data
filename = os.path.join(dirname, uuid.uuid4().hex + '.data')


def log(data):
    dt = str(pytz.timezone('Europe/Berlin').localize(datetime.now()))
    line = "{}| {}\n".format(dt, json.dumps(data))
    with open(filename, "a") as fp:
        fp.write(line)


ser = serial.Serial('/dev/ttyACM0')
while True:
    message = ser.readline()
    data = parse_data(message)
    if data:
        log(data)
