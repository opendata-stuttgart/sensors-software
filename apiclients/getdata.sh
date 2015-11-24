#!/bin/bash

# source vars
source config.sh

#tmpdir="$(mktemp -d --tmpdir dusti.sensordata.XXXX)"
tmpdir="$(mktemp -d dusti.sensordata.$(date -I).XXXX)"
echo $tmpdir

pushd "$tmpdir"
for sensorid in $SENSOR_IDS
do

	echo "sensorid $sensorid"
	mkdir -p "$sensorid"
	pushd "$sensorid"

	# get first one, parse no of pages
	wget --header "Authorization: Token $API_TOKEN"  "http://api.dusti.xyz/v1/data/?format=json&sensor=$sensorid&page=1" -O "tmp.json"
	if [ $? -ne 0 ] ;then 
		echo "error getting first data page for sensorid $sensorid"
		popd
		continue
	fi
	count=$(grep -o '"count":[0-9]*,' "tmp.json" | grep -o '[0-9]*')
	# pages are count/10+1
	npages=$(($count/10+1))
	rm "tmp.json"

	for page in $(seq -w 1 $npages)
	do
		# http://api.dusti.xyz/v1/data/?format=json&sensor=40&page=$page

		outfile="page_$page.json"
		wget --header "Authorization: Token $API_TOKEN" "http://api.dusti.xyz/v1/data/?format=json&sensor=$sensorid&page=$page" -O "$outfile"

	done
	popd
done

echo results in $tmpdir
