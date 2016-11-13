#!/bin/bash

# TODO
# auto discover device?
# check device? No, since it will appear suddenly

serialdev="/dev/ttyUSB0"
if [ -n "$1" ] ; then
	# it should be safe to call with any given filename
	serialdev="$1"
fi

if [ -z "$(which screen)" ] ; then
	echo "screen not found, please install it"
	exit 2
fi

while true
do
	screen "$serialdev"
	# little delay, so script can be stopped with ^C
	sleep 0.1
done

