#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import argparse
from influxdb import InfluxDBClient
import paho.mqtt.client as mqtt
import sys

# globals
verbosity_level=3;

# main 
def main():
    args = parse_args()
    verbosity_level=args.verbosity
    print(args)
    try:
        userdata={}
        iclient = InfluxDBClient(args.influxhost, args.influxport, args.influxuser, args.influxpass, database=args.influxdb)
        dbexists=False;
        for d in iclient.get_list_database(): 
            dbexists=args.influxdb in d.values()
            if dbexists is True:
                continue;
        if dbexists is not True:
            debug_out("creating database "+args.influxdb,3)
            iclient.create_database(args.influxdb)
    except InfluxDBClientError:
        print("influx client error, exiting...")
        sys.exit(1)

    userdata["iclient"]=iclient
    userdata["topicroot"]=args.topicroot
    
    # connect to MQTT
    mclient = mqtt.Client(client_id=sys.argv[0], clean_session=True, userdata=userdata)#, protocol=MQTTv31)
    # in constructor: mclient.user_data_set(userdata)
    if args.mqttuser is not None:
        mclient.username_pw_set(args.mqttuser, args.mqttpass)
    mclient.on_connect = on_connect
    mclient.on_disconnect = on_disconnect
    mclient.on_message = on_message
    debug_out("connecting to mqtt "+args.influxdb,3)
    try:
        mclient.connect(args.mqtthost, args.mqttport, 60)
    except ConnectionRefusedError as e:
        debug_out("connection failed: ")
        print(e)
    # mclient.subscribe.callback(on_message, args.topicroot+"#", hostname=args.mqtthost)
    #mclient.loop_forever(timeout=1.0, max_packets=1, retry_first_connection=False)
    mclient.loop_forever()

def debug_out(msg,verbosity=5):
    if verbosity>verbosity_level:
        print(msg)

def on_connect(client, userdata, flags, rc):
    debug_out("Connected with result code "+str(rc),3)
    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe(userdata["topicroot"]+"#")
    debug_out("subscribed to "+userdata["topicroot"]+"#",5)

def on_disconnect(client, userdata, rc):
    debug_out("Disconnected",3)
    
# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    debug_out(msg.topic+" "+str(msg.payload),5)
    # if topicroot is found at beginning: strip it
    ss=msg.topic.lstrip(userdata["topicroot"]).split("/")
    slen=len(ss)
    json_body={}
    if (slen)>=3:
        # split contains all parts
        json_body = {
                "measurement": ss[slen-1],
                "fields": {
                    "value": msg.payload
                },
                "tags":{
                    "sensortype": ss[slen-2],
                    "nodeid": ss[slen-3]
                }}
        userdata["iclient"].write(json_body)
    #  state_topic: "dusti/esp8266-16058770/PPD42NS/#"
    #  name: "PPD Sensor"
    #  qos: 0
    #  unit_of_measurement: "%"
    #  value_template: '{{ value }}'


def parse_args():
    parser = argparse.ArgumentParser(
        description='Forward MQTT messages to am InfluxDB')
    parser.add_argument('-i', '--influxhost',  dest='influxhost', type=str, required=False, default='localhost',
                        help='hostname of InfluxDB http API')
    parser.add_argument('-I','--influxport',  dest='influxport', type=int, required=False, default=8086,
                        help='port of InfluxDB http API')
    parser.add_argument('-m', '--mqtthost',  dest='mqtthost', type=str, required=False, default='localhost',
                        help='hostname of MQTT server')
    parser.add_argument('-M','--mqttport',  dest='mqttport', type=int, required=False, default=1883,
                        help='port of MQTT server')
    parser.add_argument('-t', '--topicroot',  dest='topicroot', type=str, required=False, default='',
                        help='only consider topics starting with topicroot')
    parser.add_argument('-o', '--omittopic', dest='omittopic', nargs='*', required=False, 
                        help="omit topics matching pattern")
    parser.add_argument('-u', '--influxuser',  dest='influxuser', type=str, required=False, default=None,
                        help='username for InfluxDB')
    parser.add_argument('-U', '--mqttuser',  dest='mqttuser', type=str, required=False, default=None,
                        help='username for MQTT')
    parser.add_argument('-p', '--influxpass',  dest='influxpass', type=str, required=False, default=None,
                        help='password for InfluxDB')
    parser.add_argument('-P', '--mqttpass',  dest='mqttpass', type=str, required=False, default=None,
                        help='password for MQTT')
    parser.add_argument('-d', '--influxdb',  dest='influxdb', type=str, required=False, default='mqtt2influx',
                        help='name of InfluxDB to store data in')
    parser.add_argument('-v', '--verbosity',  dest='verbosity', type=int, required=False, default=5,
                        help='name of InfluxDB to store data in')
    return parser.parse_args()


if __name__ == '__main__':
    #sys.exit(
    main()
    #)
    