#!/usr/bin/env python

# subsample luftdaten.info data from archive.luftdaten.info
# to hourly and daily means

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import argparse
import sys
import os
import csv
# import ggplot # for plots, currently install borken

# files are given on commandline

parser = argparse.ArgumentParser(description='Process csv from archive,dljf API')
parser.add_argument(metavar='J', type=str, nargs='+', dest='csvfilenames',
                    help='csv files to be processed')
parser.add_argument('-o', '--outdir', default='.', type=str, dest='outdir',
                    help='outdir where files (.csv) are stored')

args = parser.parse_args()

# result dict hourly
rdh={}
# result dict daily
rdd={}
cnt=np.size(args.csvfilenames)
for csvfilename in args.csvfilenames:
    with open(csvfilename) as f:
        cnt-=1;
        sys.stderr.write(str(cnt)+'.')
        sys.stderr.flush()
        dat=pd.read_csv(csvfilename, sep=";")
        if dat.size < 1:
            sys.stderr.write("no data in "+csvfilename)
            continue
        dat.index=pd.DatetimeIndex(dat["timestamp"])
        # hourly
        h=dat.resample('H')
        sid=np.int(h["sensor_id"][0])
        rdh[sid]=pd.concat([rdh.get(sid),h])
        # daily
        d=dat.resample('D')
        rdd[sid]=pd.concat([rdd.get(sid),d])
        
if not os.path.exists(args.outdir):
    os.makedirs(args.outdir)

# sort all dfs and write out to csv files
for k in rdd.keys():
    ofilen=os.path.join(args.outdir, "sensor_hourly_"+str(k)+".csv")
    with open(ofilen, 'w') as o:
        rdh[k].sort_index().to_csv(o)

    ofilen=os.path.join(args.outdir, "sensor_daily_"+str(k)+".csv")
    with open(ofilen, 'w') as o:
        rdd[k].sort_index().to_csv(o)

# dict of all sensors
das={}
for k in rdd.keys():
    for m in ['P1','P2','temperature','humidity']:
        if m in rdd[k]:
            s=rdd[k][m]
            s.name=k         
            das[m]=pd.concat([das.get(m),s],axis=1)
