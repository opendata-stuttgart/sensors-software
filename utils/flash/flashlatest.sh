#!/bin/bash

echo "usage: [esptool=esptool.py] $0 [<esptooloptions>]"

if [ -z "$esptool" ] 
then
esptool=$(which esptool.py)
if [ -z "$esptool" ] 
	then
		echo esptool.py not found, please define esptool="/path/to/esptool"
		exit 1
	fi
fi

binfile="latest.bin"
wget -c "https://www.madavi.de/sensor/update/data/$binfile"

#esptool.py write_flash -vv -cb 57600 -ca 0x00000 -cp /dev/ttyUSB0 -cf latest.bin 

read -p "patch Freifunk to XXXXXXXX? [y/N]" ans

if [ "$ans" == "y" ] 
then
	patchedbinfile="${binfile}.patched"
	hexdump -ve '1/1 "%.2X"' "$binfile" | sed "s/4672656966756E6B/5858585858585858/g" | xxd -r -p > "$patchedbinfile"
	binfile="$patchedbinfile"
fi

# flash 
esptool.py write_flash 0x00000 "$binfile" "$@"

# get info
chipid="$(esptool.py chip_id)"
chid=$(esptool.py chip_id| grep -io '0x[0-9a-fA-F]*\b')
chiddec=$(python -c "print (\"%d\"%($chid))")
mac="$(esptool.py read_mac| grep -io '[0-9a-f:]\{17\}')"
info="$chiddec\t$chid\t$mac"
echo -e "$info" | tee -a flashlist.txt


