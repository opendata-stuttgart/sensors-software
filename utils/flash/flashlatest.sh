#!/bin/bash

outappendfile=listofflashed.csv
echo "usage: [esptool=/path/to/esptool] [esptoolpy=/path/to/esptool.py] [devserial=/dev/ttyUSB0] $0"
echo "writes output to $outappendfile"

if [ -z "$esptool" ] ; then
	esptool="$(ls $HOME/.arduino*/packages/esp8266/tools/esptool/*/esptool | sort | tail -1)"
	if [ -z "$esptool" ] ; then
			echo esptool not found, please define esptool="/path/to/esptool"
			echo "https://github.com/igrr/esptool-ck/"
			exit 1
	fi
fi
if [ -z "$esptoolpy" ] ; then
	esptoolpy="$(which esptool.py)"
	if [ -z "$esptoolpy" ] ; then
		echo esptool.py not found in PATH, please define esptoolpy="/path/to/esptool.py"
		echo "https://github.com/themadinventor/esptool"
		exit 1
	fi
fi

if [ -z "$devserial" ] ; then
	devserial=/dev/ttyUSB0
	echo devserial="$devserial" \# define to change
fi
if [ ! -w "$devserial" ] ; then
	echo "no write access to $devserial"
	if [ ! -d "/dev/serial/" ] ; then 
		echo "no serial devices found in /dev/serial/, exiting"
		exit 1
	fi
	read -p "list all serial devices? [Y/n]" ans
	if [ "$ans" != "n" ] ; then
		ls -l /dev/serial/by-id/
	fi
	exit 1
fi


if [ ! -f "$outappendfile" ] ; then
	echo "nodemcuID	sensorname	hexchipID	MAC	revision:serial	email	lat	lon	locationaddress	sensorID1	sensorname1	sensorID2	sensorname2" >> "$outappendfile"
fi

# get info
chipid="$($esptoolpy chip_id)"
chid=$($esptoolpy chip_id| grep -io '0x[0-9a-fA-F]*\b')
chiddec=$(python -c "print (\"%d\"%($chid))")
mac="$($esptoolpy read_mac| grep -io '[0-9a-f:]\{17\}')"
locadr="LOCADRESS"
email="@"
lat="LAT"
lon="LON"
echo ""

read -p "ask more infos? [Y/n]" ans

if [ "$ans" != "n" ] ; then
	#examplestr="V0-000"
	#read -p "PM sensor revision (on back/flat side top left corner)? [default: $examplestr]" ans
	#if [ -n "$ans" ] ; then
#		srevision="$ans"
	#fi
	#examplestr="0000-0000"
	#read -p "PM sensor serial number (SN on sticker, besides fan, below barcode)? [default: $examplestr]" ans
	#if [ -n "$ans" ] ; then
#		sserial="$ans"
	#fi

	examplestr="70000 Stuttgart, Staubweg 00"
	read -p "Adress?  [like: $examplestr]" ans
	if [ -n "$ans" ] ; then
		locadr="$ans"
	fi
	examplestr="unknown@example.com"
	read -p "Email?  [like: $examplestr]" ans
	if [ -n "$ans" ] ; then
		email="$ans"
	fi
	examplestr="00.0000"
	read -p "latitude?  [like: $examplestr]" ans
	if [ -n "$ans" ] ; then
		lat="$ans"
	fi
	examplestr="00.0000"
	read -p "longitude?  [like: $examplestr]" ans
	if [ -n "$ans" ] ; then
		lon="$ans"
	fi
fi

info="DBID\tesp8266-$chiddec\t$chid\t$mac\t$srevision:$sserial\t$email\t$lat\t$lon\t$locadr\tSID1\tSNAME1\tSID2\tSNAME2"
echo -e "$info" | tee -a "$outappendfile"


#esptool.py write_flash -vv -cb 57600 -ca 0x00000 -cp /dev/ttyUSB0 -cf latest.bin 

read -p "patch Freifunk to XXXXXXXX? [y/N] " ans

binfile="latest.bin"
wget -c "https://www.madavi.de/sensor/update/data/$binfile"

if [ "$ans" == "y" ] 
then
	patchedbinfile="${binfile}.patched"
	hexdump -ve '1/1 "%.2X"' "$binfile" | sed "s/4672656966756E6B/5858585858585858/g" | xxd -r -p > "$patchedbinfile"
	binfile="$patchedbinfile"
fi

# flash 
# esptool.py write_flash 0x00000 "$binfile" "$@"


read -p "flash now? [y/N] " ans
if [ "$ans" == "y" ] 
then
	$esptool -vv -cd nodemcu -cb 57600 -ca 0x00000 -cp "$devserial" -cf "$binfile"
fi


echo "to erase SPIFF (config data) use arduino IDE and https://github.com/esp8266/arduino-esp8266fs-plugin"
echo "see https://github.com/esp8266/arduino-esp8266fs-plugin"
#[SPIFFS] data   : /home/martin/hft/applications/finedust/sensors-software/esp8266-arduino/ppd42ns-wificonfig-ppd-sds-dht/data
#[SPIFFS] size   : 3052
#[SPIFFS] page   : 256
#[SPIFFS] block  : 8192
#[SPIFFS] upload : /tmp/buildae19241fabc98f54562c84b5c3712165.spiffs/ppd42ns-wificonfig-ppd-sds-dht.spiffs.bin
#[SPIFFS] address: 0x100000
#[SPIFFS] reset  : nodemcu
#[SPIFFS] port   : /dev/ttyUSB0
#[SPIFFS] speed  : 115200

read -p "or overwrite SPIFFS now? [y/N] " ans

if [ "$ans" == "y" ] ; then
	
	spiffbin=empty.spiffs.bin
	if [ ! -f "$spiffbin" ] ; then
		bunzip2 -k "${spiffbin}.bz2"
	fi

	$esptool -vv -cd nodemcu -cb 115200 -ca 0x100000 -cp "$devserial" -cf "$spiffbin"
fi

