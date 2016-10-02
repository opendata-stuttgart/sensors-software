#!/bin/bash

outappendfile=listofflashed.csv
echo "usage: [esptool=esptool.py] $0 [<esptooloptions>]"
echo "writes output to $outappendfile"

if [ -z "$esptool" ] 
then
esptool=$(which esptool.py)
if [ -z "$esptool" ] 
	then
		echo esptool.py not found, please define esptool="/path/to/esptool"
		exit 1
	fi
fi

if [ ! -f "$outappendfile" ] ; then
	echo "sensorID	sensorname	hexchipID	MAC	shortname	email	lat	lon	locationaddress	sensorID1	sensorname1	sensorID2	sensorname2" >> "$outappendfile"
fi

# get info
chipid="$(esptool.py chip_id)"
chid=$(esptool.py chip_id| grep -io '0x[0-9a-fA-F]*\b')
chiddec=$(python -c "print (\"%d\"%($chid))")
shortname="$chiddec"
mac="$(esptool.py read_mac| grep -io '[0-9a-f:]\{17\}')"
echo ""
read -p "You have a shortname? [default: $shortname]" ans
if [ -n "$ans" ] ; then
	shortname="$ans"
fi
info="DBID\tesp8266-$chiddec\t$chid\t$mac\t$shortname\tEMAIL\tLAT\tLON\tLOCADDRESS\tSID1\tSNAME1\tSID2\tSNAME2"
echo -e "$info" | tee -a "$outappendfile"



#esptool.py write_flash -vv -cb 57600 -ca 0x00000 -cp /dev/ttyUSB0 -cf latest.bin 

read -p "patch Freifunk to XXXXXXXX? [y/N]" ans

binfile="latest.bin"
wget -c "https://www.madavi.de/sensor/update/data/$binfile"

if [ "$ans" == "y" ] 
then
	patchedbinfile="${binfile}.patched"
	hexdump -ve '1/1 "%.2X"' "$binfile" | sed "s/4672656966756E6B/5858585858585858/g" | xxd -r -p > "$patchedbinfile"
	binfile="$patchedbinfile"
fi

# flash 
esptool.py write_flash 0x00000 "$binfile" "$@"

