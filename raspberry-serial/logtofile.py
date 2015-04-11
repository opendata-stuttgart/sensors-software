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

from sensor import SensorPPD42NS, SensorSHT10

dirname = os.path.dirname(os.path.abspath(__file__))
# different filename on each restart
# because you may have to change the location of the sensor
# before uploading the data
filename = os.path.join(dirname, uuid.uuid4().hex)

ser = serial.Serial('/dev/ttyACM0')
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
