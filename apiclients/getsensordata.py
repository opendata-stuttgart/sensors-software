#!/usr/bin/env python

# TODO: fails for multiple sensor types/messages (multisens)
# handle this better (check dict keys/combine)
# TODO: requests via https (we have a token to secure)
import json
import argparse
import sys
import csv
import urllib2
import pandas as pd
#import string
from urllib2 import urlopen
try:
    from config import API_TOKEN
except:
    print ("could not load from config.py, please create and add API_TOKEN = 'YOURTOKEN'")
    sys.exit(2)
# files are given on commandline or downloaded from api via sensor number


class DustiApi(object):
    """class to handle the dusti API"""
    nextpageurl=None
    sensorid=None
    apiendpoint='http://api.dusti.xyz/v1/data/'
    page=1
    sensordata=pd.DataFrame() # TODO: which data type, pandas series/df?
    # DataFrame is fine, missing/new columns are added as needed
    maxmeas=None
    def __init__(self,sensorid,apiendpoint,maxmeas=None):
        self.setSensorID(sensorid)
        self.setApiEndpoint(apiendpoint)
        self.maxmeas=maxmeas
    def setSensorID(self,newsensorid):
        if newsensorid is None:
            raise ValueError('DustiApi: sensorid is None')
        self.sensorid=newsensorid
    def setApiEndpoint(self,newapiendpoint):
        if newapiendpoint is not None:
            self.apiendpoint=newapiendpoint
    def fetchpage(self,page=1):
        self.page=page
        apigeturl=self.apiendpoint+'?format=json&sensor='+str(self.sensorid)+'&page='+str(page)
        try:
            req = urllib2.Request(apigeturl)
            req.add_header('Authorization', 'Token '+API_TOKEN)
            r = urllib2.urlopen(req)
            jsondata = r.read()
            return jsondata
        except IOError as (errno, strerror):
            sys.stdout.write("I/O error({0}): {1}".format(errno, strerror))
            return None
    def fetchnextpage(self): 
        self.page+=1
        return self.fetchpage()
    def result2dict(self,r):
        rd={}
        for e in r:
            rd[u'timestamp']=pd.to_datetime(e[u'timestamp'],utc=True)
            for m in e['sensordatavalues']:
                rd[m['value_type']]=float(m['value'])
                #[1]['sensordatavalues'][1]['value_type']
        return rd
    def result2df(self,r):
        return pd.DataFrame(self.result2dict(r))
    def parseaddsensordata(self,jsonstr):
        j=json.loads(jsonstr)
        for r in j:
            rd=self.result2df(r)
            self.sensordata.append(rd)
    def getdata(self):
        # what values do we have?
        # iterate over any
        return self.sensordata

class json2csv_unused(object):
    csvrowdicts=[] # list of dicts for each row
    csvwriter=None
    def json2csvdict(jsonstr):
        pass
    def json2csvfile(jsonstr,csvfilehandle,printheader=False):
        printcsvheader=True
        for r in jsonstr['results']:
            csvdict={}
            csvdict['timestamp']=r['timestamp']
            for v in r['sensordatavalues']:
                csvdict[v['value_type']]=v['value']
        return csvdict
        if printheader:
            fieldnames=csvdict.keys()
            csvwriter = csv.DictWriter(csvout, fieldnames=csvdict.keys())
            csvwriter.writeheader()
            printcsvheader=False
        csvwriter.writerow(csvdict)

parser = argparse.ArgumentParser(description='Process json from dusti API to CSV')
parser.add_argument('-s', '--sensorid', type=int, default=None, dest='sensorid', required=False,
                   help='sensorid of sensor to fetch data via api')
parser.add_argument('-o', '--outfile', default=None, type=str, dest='outfile',
                    help='output filename (.csv), if not given print to stdout')
parser.add_argument('-a', '--apiendpoint', default='http://api.dusti.xyz/v1/data/', 
                    help='endpoint of API')
parser.add_argument('-m', '--maxvalues', type=int, default=None, dest='maxvalues',
                   help='maximum number of values to fetch')
# files are given on commandline
parser.add_argument(metavar='J', type=str, nargs='*', dest='jsonfilenames',
                    help='json files to be processed')

args = parser.parse_args()

print(args)

da=DustiApi(sensorid=args.sensorid,apiendpoint=args.apiendpoint)
# measurements dict for the result
md={}
printcsvheader=True
getnextpage=True
#jsonfilename=
# get the json directly via api
#res=da.apifetch(sensorid=args.sensorid,apiendpoint=args.apiendpoint,page=1)
#if res is None:
    #sys.stdout.write('error fetching first page from api')
    #getnextpage=False
#while getnextpage:
    #res=apifetch
    #j=json.loads(res)


for jsonfilename in args.jsonfilenames:
    with open(jsonfilename) as f:
        j=json.load(f)
        nextfile=j['next']
        for r in j['results']:
            rd=result2dict(r)
            if md["_".join(sorted(rd.keys()))] is None:
                md["_".join(sorted(rd.keys()))]=[rd]
            else:
                md["_".join(sorted(rd.keys()))].append(rd)
            # merge into one frame or multiple frames/csvs?

            
            #csvdict={}
            #csvdict[u'timestamp']=r['timestamp']
            #for v in r['sensordatavalues']:
                #csvdict[v['value_type']]=v['value']
            #if printcsvheader:
                #fieldnames=csvdict.keys()
                #csvwriter = csv.DictWriter(csvout, fieldnames=csvdict.keys())
                #csvwriter.writeheader()
                #printcsvheader=False
            #csvwriter.writerow(csvdict)

# close csvout file handler

csvfilename=args.outfile
if csvfilename is None:
    csvout=sys.stdout
else:
    csvout=open(csvfilename,'w')
    # TODO do stuff here
    csvout.close()

#sys.exit()

# use pd series
#d=pd.read_json(jsonfilename)
#s=pd.Series(csvdict)
#pd.DatetimeIndex(pd.to_datetime(s.keys()),utc=True))
#s=
#pd.to_datetime(s.timestamp)
