#!/bin/bash

# remove index.html before fetching
rm archive.luftdaten.info/index.html -f

# mirror the archive via wget
wget -r -c -np -nc -N -k http://archive.luftdaten.info/
