import requests
import json
from config import SENSOR_UID


def parse_data(message):
    # mapping for api sensor_types
    message = message.replace('lowpulseoccupancy', 'dur')
    message = message.replace('count', '')

    # some checks to elimanate some of the 400s from the API
    if ':' not in message or len(message.split(':')) != 7:
        return False
    if ';' not in message or len(message.split(';')) != 6:
        return False

    return dict(map(lambda x: x.split(':'), message.split(';')))


def send_data(data, timestamp=None):
#    url = "https://api.dusti.xyz/v1/push-sensor-data/"
    url = "http://localhost:8000/v1/push-sensor-data/"

    payload = {
        "sampling_rate": "15000",
        "sensordatavalues": []
    }
    if timestamp:
        payload['timestamp'] = timestamp

    for key, value in data.iteritems():
        d = {'value': value, 'value_type': key}
        payload['sensordatavalues'].append(d)

    headers = {'SENSOR': SENSOR_UID,
               'Content-Type': 'application/json'}
    r = requests.post(url, data=json.dumps(payload),
                      headers=headers, verify=False)
    print(r.status_code)
    print(r.text)
