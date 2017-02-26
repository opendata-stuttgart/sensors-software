#!/bin/bash


source "$(dirname $0)/mailconfig.sh"
if [ -z "$lfile" ] ; then
	lfile=listofflashed.csv
else
	if [ ! -f "$lfile" ] ; then
		echo "lfile=$lfile not found"
	fi
fi
#testlist.csv
echo "using input file: $lfile"

subject="[luftdaten.info] Sensor in der Datenbank, es kann losgehen"
while [ -z "$sender" ] 
do
    read -p "email to send from: " sender
done
while [ -z "$smtpserver" ]
do
    read -p "SMTP server to send from: " smtpserver
done

bodyfixedcontent="
Hallo, 

hier kommen ein paar Infos zu deiner Sensorstation (Feinstaubmessstation). 
* Die Station ist jetzt in unserer Datenbank eingetragen und wird daher, sobald sie online ist, Daten aufzeichnen.
* Anleitung zum Konfigurieren des eigenen WLAN: https://github.com/opendata-stuttgart/meta/wiki/Konfiguration-der-Sensoren
* Ich habe die Koordinaten nach Adresse herausgesucht, sie sind in der Datenbank (aber evtl. nicht hier in der Mail)
* Wer da Bedenken hat und das anonymisiert haben will, sage mir Bescheid. Die personenbezogenen Daten (Adresse, Email) werden nicht weitergegeben und sind nicht 'Open Data'. Koordinaten (lat/lon) werden auf 3 Stellen gerundet, das entspricht etwa Rechtecken von ca 70x110m (wen das genauer interessiert: hier ist eine Visualisierung des Punkterasters: https://github.com/Marwe/particlemap/blob/master/static/grid001.json und https://github.com/Marwe/particlemap/blob/master/static/raster_0.001_degree.png )
* Es wäre gut, wenn ich (sofern nicht schon vorhanden) noch eine kurze Beschreibung haben könnte, wie die Sensorumgebung ist, ich habe für meinen Sensor z.B. recht ausführlich geschrieben: 'Sensor an Außenwand, Höhe über Grund: 7m, Dachüberstand in + 2m darüber. Straßenseite mit keinem Verkehr nachts, tagsüber besonders zu rush hours.'
* Die Angaben enthalten IDs, mit denen die eigenen Sensordaten identifiziert werden können: die erste Zahl (vor esp8266-xxxx) ist die Node-ID (für das Rechnermodul), hinten folgen noch einmal zwei IDs für die Sensoren, die wichtiger sind, da diese in der Karte und in den Exportdaten auftauchen, z.B. im Dateinamen und in den CSV-Dateiexporten http://archive.luftdaten.info/2017-01-10/
* Die Karten: 
    * SDS011 https://www.madavi.de/sensor/feinstaub-map-sds/ 
    * DHT22 https://www.madavi.de/sensor/feinstaub-map-dht/
* Für Updates zum Projekt schau bei mal wieder bei http://luftdaten.info/ vorbei


Hier die Infos zu deinem Sensor in einer Zeile:

$(head -1 $lfile)

"



read -s -p "Password for smtp for $sender: " smtpw

if [ -z "$smtpw" ] ; then
	echo "pw empty, exiting"
	exit 1
fi

maxcnt=200
cnt=0
tmpmail=$(mktemp -d)

#for rec in $(grep -E -o "\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,6}\b" $lfile )
# \t does not work properly, replace with |

sed -e 's#\t#|#g' $lfile | while IFS="|" read nodemcuID	sensorname	hexchipID	MAC	revisionserial	email	lat	lon	locationaddress	sensorID1	sensorname1	sensorID2	sensorname2
do
	cnt=$((cnt+1))
	if [ $cnt -gt $maxcnt ] ; then
		echo "maxcnt=$maxcnt reached, stopping."
		exit 0
	fi
	# check, if there is a mail in the line
        #if [ -z "$(echo "$sinfo" | grep -E -o "\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,6}\b")" ] ; then
	if [ -z "(echo $email| grep -E -o '\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,6}\b')" ] ; then
		echo "no mail in line $cnt, skipping"
		continue
	fi
	
	subject="[luftdaten.info] Sensorstation $sensorname ist in der Datenbank, es kann losgehen"
    bodypre="Bcc:<$sender>
Subject:${subject}"

	rec="$email"
	sinfo="$nodemcuID	$sensorname	$hexchipID	$MAC	$revisionserial	$email	$lat	$lon	$locationaddress	$sensorID1	$sensorname1	$sensorID2	$sensorname2"
	#nodeid=$(awk -F "\t" "/$rec/{print $2}" $lfile)
	#sensorid1=$(awk -F "\t" "/$rec/{print $10}" $lfile)
	#sensorid2=$(awk -F "\t" "/$rec/{print $12}" $lfile)
	lats=$(echo "$lat"| grep -o '[0-9-]*\.[0-9][0-9][0-9]'}
	lons=$(echo "$lon"| grep -o '[0-9-]*\.[0-9][0-9][0-9]'}
		
	customlinks="
	
Ob der Sensor funktioniert und Daten liefert, kann auf https://www.madavi.de/sensor/graph.php eingesehen werden, wahrscheinlich sind deine Sensorseiten:
https://www.madavi.de/sensor/graph.php?sensor=${sensorname}-sds011
https://www.madavi.de/sensor/graph.php?sensor=${sensorname}-dht

Sollten die Daten nur unregelmäßig erscheinen, kann es am WLAN liegen, checke bitte die Signalseite:
https://www.madavi.de/sensor/signal.php?sensor=${sensorname}

In den Karten und Exporten haben die Sensoren die Nummern: 
$sensorname1	$sensorID1
$sensorname2	$sensorID2

Die eingetragene Position ist:
http://www.openstreetmap.org/?mlat=$lat&mlon=$lon#map=18/$lat/$lon
herausgegeben wird nur die gerundete Position:
http://www.openstreetmap.org/?mlat=$lats&mlon=$lons#map=18/$lats/$lons

Viel Spaß und neue Einsichten
Martin Weis
"

	body="To:<${rec}>
$bodypre
$bodyfixedcontent"
	mailtextfile="$tmpmail/$rec"
	echo "$body" "$sinfo" "$customlinks" | tee "$mailtextfile" 

done

for mailtextfile in "$tmpmail"/*@*
do

    cat "$mailtextfile"
    echo "$mailtextfile"
    
    read -p "send? [y/N]" ans
    if [ "$ans" == "y" ] ; then
        cat "$mailtextfile" | s-nail -v \
        -r "$sender" \
        -S smtp="$smtpserver" \
        -S smtp-use-starttls \
        -S smtp-auth=login \
        -S smtp-auth-user="$sender" \
        -S smtp-auth-password="$smtpw" \
        -S ssl-verify=ignore \
        -t # specify To: Cc: Bcc: on body
        #"$sender;$rec"
        #      -s "$subject" \
        
        success="$?"
        if [ "$success" != "0" ] ; then
            read -p "sending of message failed ($success), continue? [n/y]" ans
            if [ "$ans" != "y" ] ; then
                echo "exiting"
                exit 2
            fi
        fi
    fi

done

echo tmpfiles in $tmpmail
