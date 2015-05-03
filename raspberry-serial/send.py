#
# send file to API
#
#
import json
import sys

from sensor import (
    SensorDSM501A,
    SensorGP2Y10,
    SensorPPD42NS,
    SensorSHT10,
    SensorBMP180,
)

if len(sys.argv) != 2:
    print("python send.py <filename>")

# get type from filename
filename = sys.argv[1]
for cls in (SensorDSM501A, SensorGP2Y10, SensorPPD42NS,
            SensorSHT10, SensorBMP180):
    if filename.lower().endswith(cls.sensor_type.lower()):
        instance = cls()
        break

assert instance

with open(filename, 'r') as fp:
    for line in fp.readlines():
        timestamp = line.split('|')[0]

        data = json.loads(line.split('|')[1])
        data = instance.filter(data)
        if data:
            print(data)
#            instance.send(data, timestamp)
