#
# send file to API
#
#
import json
import sys

from sensor import SensorPPD42NS, SensorSHT10, SensorGP2Y10

if len(sys.argv) != 2:
    print("python send.py <filename>")

with open(sys.argv[1], 'r') as fp:
    for line in fp.readlines():
        timestamp = line.split('|')[0]

        data = json.loads(line.split('|')[1])
        ppd = SensorPPD42NS()
        data = ppd.filter(data)
        if data:
            ppd.send(data, timestamp)

        data = json.loads(line.split('|')[1])
        sht10 = SensorSHT10()
        data = sht10.filter(data)
        if data:
            sht10.send(data, timestamp)

        data = json.loads(line.split('|')[1])
        gp2y10 = SensorGP2Y10()
        data = gp2y10.filter(data)
        if data:
            gp2y10.send(data, timestamp)
