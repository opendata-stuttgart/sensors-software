#
# send file to API
#
#
import json
import sys

from utils import send_data

if len(sys.argv) != 2:
    print("python send.py <filename>")

with open(sys.argv[1], 'r') as fp:
    for line in fp.readlines():
        timestamp = line.split('|')[0]
        data = json.loads(line.split('|')[1])
        if data:
            send_data(data, timestamp)
