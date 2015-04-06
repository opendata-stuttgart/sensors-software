# Particulates sensor usage with RaspberryPi


## Usage

Connect sensor with Arduino via usb to RaspberryPi.
The Arduino has the serial software for the sensor installed and prints the sensor results.
A python script is pushing the results to our API endpoint.


## Install dependencies

for raspbian

```
# for push
sudo apt-get update
sudo apt-get install -y python-requests python-serial
# for logtofile
sudo apt-get install -y python-pip
sudo pip install pytz
```

checkout the source repository

```
cd /home/pi
git clone https://github.com/opendata-stuttgart/sensors-software.git
```


## IMPORTANT

set SENSOR_UID in push.py !!

## run to log live

```
python push.py
```

## run to write to file

```
python logtofile.py
```


## autorun logotfile.py on startup

add this to your ``/etc/rc.local``:

```
/bin/sleep 15 && python /home/pi/sensors-software/raspberry-serial/logtofile.py
```

before the ``exit 0`` line

## send data to server later

```
python send.py <filename>
```
