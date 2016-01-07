#!/usr/bin/env python

#import json
import argparse
import os
import sys
import csv
#import urllib2
import pandas as pd
#import string
#from urllib2 import urlopen
import datetime
import dateutil
import requests

parser = argparse.ArgumentParser(description='Get CSV data from archive')
parser.add_argument('-s', '--sensorid', type=int, default=None, dest='sensorid', required=True,
                   help='sensorid of sensor to fetch data via api')
parser.add_argument('-c', '--cachedir', default='csvcache', 
                    help='cached csv filedir')
parser.add_argument('-b', '--baseurl', default='http://archive.madflex.de', 
                    help='base URL (without trailing /)')
parser.add_argument('-n', '--ndays', type=int, default=30, dest='ndays',
                   help='maximum number of days to fetch values for')
parser.add_argument('-l', '--lastday', type=str, default=str(datetime.date.today()-datetime.timedelta(1)), dest='lastday',
                   help='last day to fetch values for, defaults to yesterday')

# files are given on commandline
#parser.add_argument(metavar='J', type=str, nargs='*', dest='jsonfilenames',
                    #help='json files to be processed')

args = parser.parse_args()


try:
    ldate=dateutil.parser.parse(args.lastday).date()
except ValueError as e:
    print "error parsing lastday:"+e.message
    sys.exit(1)

# TODO: create cachedir, if not existent
if not os.path.isdir(args.cachedir):
    os.makedirs(args.cachedir)

df=pd.DataFrame()

for daydiff in range(args.ndays):
    datetoget=ldate-datetime.timedelta(daydiff)
    basefilename=str(datetoget)+"_ppd42ns_sensor_"+str(args.sensorid)+".csv"
    fetchurl=args.baseurl+"/"+str(datetoget)+"/"+basefilename
    cachefile=os.path.join(args.cachedir,basefilename)
    if not os.path.exists(cachefile):    
        print "file"+cachefile+" not cached, getting from server"
        try:
            print fetchurl
            r=requests.get(fetchurl)
            if len(r.text) == 0:
                print "fetched no data"
                continue
            with open(cachefile,"w") as f:
                f.write(r.text)
            
        except IOError as (errno, strerror):
            sys.stdout.write("I/O error({0}): {1}".format(errno, strerror))
            continue
    # add to dataframe
    with open(cachefile,"r") as f:
        df=df.append(pd.read_csv(f))

    




