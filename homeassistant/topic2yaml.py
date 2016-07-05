#!/usr/bin/env python
# -*- coding: utf-8 -*-

import paho.mqtt.client as mqtt
import os.path

mqtthost="mqtt.opendataset.click"
mqttport=1883
topicroot="dusti/" # topics start with topicroot
# only topics defined here will be used
unitdict={
    "P1":"1/cf",
    "P2":"1/cf",
    "durP1":"ns",
    "durP2":"ns",
    "ratioP1":"1",
    "ratioP2":"1",
    "temperature":"°C",
    "humidity":"%"
}

seentopics={}

def on_connect(client, userdata, flags, rc):
    #print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe(topicroot+"#")

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    #print(msg.topic+" "+str(msg.payload))
    if seentopics.get(msg.topic) is not None:
        return
    seentopics[msg.topic]=1
    # if topicroot is found at beginning: strip it
    # split the remaining topic
    ss=msg.topic.lstrip(topicroot).split("/")
    # if topic is in unitdict, output
    if unitdict.get(ss[len(ss)-1]) is not None:
        configstr ='  - platform: mqtt\n'
        configstr+='    state_topic: "'+msg.topic+'"\n'
        configstr+='    name: "'+msg.topic.lstrip(topicroot)+'"\n'
        configstr+='    qos: 0\n'
        configstr+='    unit_of_measurement: "'+unitdict.get(ss[len(ss)-1])+'"\n'
        configstr+='    value_template: \'{{ value }}\'\n'
        print (configstr)
    #  state_topic: "dusti/esp8266-16058770/PPD42NS/#"
    #  name: "PPD Sensor"
    #  qos: 0
    #  unit_of_measurement: "%"
    #  value_template: '{{ value }}'

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(mqtthost, mqttport, 60)

# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
client.loop_forever()
