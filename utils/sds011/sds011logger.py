#!/usr/bin/env python
import serial
import datetime, time
import sys

# class adapted from https://github.com/FriskByBergen/RPiParticle/blob/master/lib/sds011.py

class SDS011(object):
    msg_start  = 170
    msg_cmd    = 192
    msg_end    = 171
    sleep_time = 0.01
    device     = None
    
    def __init__(self,serialdevice="/dev/ttyUSB0"):
        self.device=serial.Serial(serialdevice, baudrate=9600, stopbits=1, parity="N",  timeout=2)

    def read(self):

        # Read in loop until message start: AAC0
        while True:
            s = self.device.read(1)
            if ord(s) == SDS011.msg_start:
                s = self.device.read(1)
                if ord(s) == SDS011.msg_cmd:
                    break
            time.sleep( SDS011.sleep_time )

        s = self.device.read(8)
                
        pm25hb = ord(s[0])
        pm25lb = ord(s[1])
        pm10hb = ord(s[2])
        pm10lb = ord(s[3])
        d5     = ord(s[4])
        d6     = ord(s[5])

        cs     = ord(s[6])
        tail   = ord(s[7]) 
        
        cs_expected = (pm25hb + pm25lb + pm10hb + pm10lb + d5 + d6) % 256
        if cs != cs_expected:
            raise Exception("Checksum test failed")

        if tail != SDS011.msg_end:
            raise Exception("Message was not correctly terminated?")

        pm25 = float(pm25hb + pm25lb*256)/10.0
        pm10 = float(pm10hb + pm10lb*256)/10.0
                
        return (pm10 , pm25)

def main():
    serialdevice="/dev/ttyUSB0"
    if len(sys.argv) > 1:
        serialdevice=sys.argv[1]
    sdslog=SDS011(serialdevice)
    # init datetime object
    dt=datetime.datetime.now()
    while True:
        try:
            pm25,pm10=sdslog.read()
            print ("%s\t%.1f\t%.1f"%(dt.utcnow(),pm25,pm10))
        except Exception as e:
            print (e.message)
if __name__ == '__main__':
    main()
